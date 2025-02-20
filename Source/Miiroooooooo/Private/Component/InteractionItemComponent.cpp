// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InteractionItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MiiroooPlayerController.h"
#include "HUDWidget.h"
#include "ItemStructure.h"
#include "BaseItem.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AInteractionItemComponent::AInteractionItemComponent()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/GameContent/Item/ItemData/DT_ItemData.DT_ItemData"));
	if (DataTable.Succeeded())
	{
		ItemData = DataTable.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed Find DataTable"));
	}

	bIsUsedInventory.SetNum(InventoryTotal);
	ItemInventory.SetNum(InventoryTotal);
}

void AInteractionItemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractionItemComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//-----Reset-----
void AInteractionItemComponent::SetItemData()
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

	ItemTotal = ItemCount;
}
//------

//-----overlapItem-----
void AInteractionItemComponent::OverlapItem()
{
	bIsOverlapItem=true;
}

void AInteractionItemComponent::UnOverlapItem()
{
	bIsOverlapItem = false;
}
//-------

//-----PickUpItem-----
void AInteractionItemComponent::PickUpAnItem()
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

void AInteractionItemComponent::PressUseItem(int KeyNum)
{
	switch (KeyNum)
	{
		case 1:
			if (bIsUsedInventory[KeyNum - 1])
			{
				FString ItemName = ItemInventory[KeyNum-1].ToString();
				UE_LOG(LogTemp, Warning, TEXT("Use Item Name1 : %s"), *ItemName); 
			}
			break;
		case 2:
			if (bIsUsedInventory[KeyNum - 1])
			{
				FString ItemName2 = ItemInventory[KeyNum - 1].ToString();
				UE_LOG(LogTemp, Warning, TEXT("Use Item Name2 : %s"), *ItemName2);
			}
			break;
		case 3:
			if (bIsUsedInventory[KeyNum - 1])
			{
				FString ItemName3 = ItemInventory[KeyNum - 1].ToString();
				UE_LOG(LogTemp, Warning, TEXT("Use Item Name3 : %s"), *ItemName3);
			}
			break;
		case 4:
			if (bIsUsedInventory[KeyNum - 1])
			{
				FString ItemName4 = ItemInventory[KeyNum - 1].ToString();
				UE_LOG(LogTemp, Warning, TEXT("Use Item Name4 : %s"), *ItemName4);
			}
			break;
		case 5:
			if (bIsUsedInventory[KeyNum - 1])
			{
				FString ItemName5 = ItemInventory[KeyNum - 1].ToString();
				UE_LOG(LogTemp, Warning, TEXT("Use Item Name5 : %s"), *ItemName5);
			}
			break;
	}
}

EItemName AInteractionItemComponent::GetRandomItem()
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

void AInteractionItemComponent::AddItem(FName ItemName)
{
	AMiiroooPlayerController* PlayerController = Cast<AMiiroooPlayerController>(GetWorld()->GetFirstPlayerController());
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

FName AInteractionItemComponent::EnumValueToFName(EItemName Value)
{
	UEnum* EnumClass = StaticEnum<EItemName>();
	FName ItemName = EnumClass->GetNameByValue(static_cast<int64>(Value));
	FString FullName = ItemName.ToString();
	FName Name = FName(*FullName.RightChop(FullName.Find(TEXT("::")) + 2));

	return Name;
}

UTexture2D* AInteractionItemComponent::GetItemTexture(FName ItemName)
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
