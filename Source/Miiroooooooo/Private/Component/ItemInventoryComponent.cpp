// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ItemInventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MiiroooPlayerController.h"
#include "ItemStructure.h"
#include "BaseItem.h"
#include "UsableItem.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values for this component's properties
UItemInventoryComponent::UItemInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UDataTable> ItemDataTable(TEXT("/Game/GameContent/Item/ItemData/DT_ItemData.DT_ItemData"));
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemClassDataTable(TEXT("/Game/GameContent/Item/ItemData/DT_ItemClass.DT_ItemClass"));
	if (ItemDataTable.Succeeded() && ItemClassDataTable.Succeeded())
	{
		ItemData = ItemDataTable.Object;
		ItemClassData = ItemClassDataTable.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemComponent::Failed Find DataTable"));
	}

	bIsUsedInventory.SetNum(InventoryTotal);
	ItemInventory.SetNum(InventoryTotal);
}


// Called when the game starts
void UItemInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AMiiroooPlayerController>(GetWorld()->GetFirstPlayerController());
	
}

// Called every frame
void UItemInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//-----Set Item Table-----
void UItemInventoryComponent::SetItemData()
{
	TArray<FItemInformation*> Rows;
	check(ItemData);
	ItemData->GetAllRows<FItemInformation>(TEXT("ItemDataTable"), Rows);

	int32 ItemCount = 0;

	for (FItemInformation* Row : Rows)
	{
		ItemCount++;

		EItemName Name = Row->ItemName;
		float Probability = Row->Probability;
		ItemProbabilisticInfo.Add(Name, Probability);
		ProbabilitySum += Probability;
	}

	SetItemClassData();

}
void UItemInventoryComponent::SetItemClassData()
{
	TArray<FItemClass*> Rows;
	check(ItemClassData);
	ItemClassData->GetAllRows<FItemClass>(TEXT("ItemClassDataTable"), Rows);
	for (FItemClass* Row : Rows)
	{
		EItemName Name = Row->ItemName;
		FName ItemName = EnumValueToFName(Name);

		UWorld* World = GetWorld();
		ABaseItem* ItemClass = World->SpawnActor<ABaseItem>(Row->ItemClass);

		ItemClassInfo.Add(ItemName, ItemClass);
	}
}
//------

//-----overlapItem-----
void UItemInventoryComponent::OverlapItem()
{
	bIsOverlapItem = true;
}

void UItemInventoryComponent::UnOverlapItem()
{
	bIsOverlapItem = false;
}
//-------

//-----PickUpItem-----
void UItemInventoryComponent::PickUpAnItem()
{
	if (bIsOverlapItem)
	{
		EItemName EnumItemName = GetRandomItem();
		FName ItemName = EnumValueToFName(EnumItemName);
		AddItem(ItemName);

		if (!ItemInventory.Contains(ItemName))
		{
			for (int i = 0; i < InventoryTotal; i++)
			{
				if (!bIsUsedInventory[i])
				{
					ItemInventory[i] = ItemName;
					bIsUsedInventory[i] = true;
					break;
				}
			}
		}
	}
}

EItemName UItemInventoryComponent::GetRandomItem()
{
	if (ProbabilitySum > 0.f)
	{
		// 구간 0 ~ ProbabilitySum-1 중 랜덤으로 숫자 하나 뽑음
		int32 RandValue = FMath::RandRange(0.f, (ProbabilitySum * 100) - 1);

		// 그 구간에 맞는 확률을 가진 아이템을 찾아 반환
		int32 Panel = 0.f;
		for (auto& Item : ItemProbabilisticInfo)
		{
			Panel += Item.Value * 100;
			if (RandValue < Panel)
			{
				return Item.Key;
			}
		}
	}
	else
	{
		SetItemData();
		GetRandomItem();
	}

	return EItemName();
}

void UItemInventoryComponent::AddItem(FName ItemName)
{
	
	if (OwnItemList.Contains(ItemName))
	{
		OwnItemList[ItemName]++;
		PlayerController->UpdateItemToInventory(ItemName, OwnItemList[ItemName]);
	}
	else
	{
		OwnItemList.Add(ItemName, 1);
		UTexture2D* Texture = GetItemTexture(ItemName);
		PlayerController->AddItemToInventory(ItemName, Texture);
	}
}
//--------

//-----Use Item-----
void UItemInventoryComponent::PressUseItem(int KeyNum)
{
	FName ItemName = ItemInventory[KeyNum - 1];
	if (bIsUsedInventory[KeyNum - 1] && OwnItemList[ItemName] > 0)
	{
		ABaseItem* ItemClass = *ItemClassInfo.Find(ItemName);
		AUsableItem* UsableItem = Cast<AUsableItem>(ItemClass);
		if (UsableItem->bIsAvailableItem())
		{
			UsableItem->UseItem();
			OwnItemList[ItemName]--;
			PlayerController->UpdateItemToInventory(ItemName, OwnItemList[ItemName]);

			if (OwnItemList[ItemName] <= 0)
			{
				int32 Index = ItemInventory.Find(ItemName);
				ItemInventory[Index] = "";
				bIsUsedInventory[Index] = false;
				// AddItem에서 else{texture 정보까지 controller에 전달}하기 위해 remove
				OwnItemList.Remove(ItemName);
				PlayerController->UpdateItemToInventory(ItemName, 0);
			}
		}
	}
}
//--------

FName UItemInventoryComponent::EnumValueToFName(EItemName Value)
{
	UEnum* EnumClass = StaticEnum<EItemName>();
	FName ItemName = EnumClass->GetNameByValue(static_cast<int64>(Value));
	FString FullName = ItemName.ToString();
	FName Name = FName(*FullName.RightChop(FullName.Find(TEXT("::")) + 2));

	return Name;
}



UTexture2D* UItemInventoryComponent::GetItemTexture(FName ItemName)
{
	FItemInformation* Row = ItemData->FindRow<FItemInformation>(ItemName, TEXT("ItemStructure"));
	if (Row)
	{
		return Row->Texture;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUDWidget : Can't find ItemName from DataTable"));
		return nullptr;
	}
}
