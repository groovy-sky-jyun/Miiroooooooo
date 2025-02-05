// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InteractionItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PlayerCharacter.h"
#include "HUDWidget.h"
#include "ItemStructure.h"
#include "BaseItem.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AInteractionItemComponent::AInteractionItemComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/GameContent/Item/ItemData/DT_ItemData.DT_ItemData"));
	if (DataTable.Succeeded())
	{
		ItemData = DataTable.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed Find DataTable"));
	}

	
	OverlapItems.Empty();
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
void AInteractionItemComponent::SetUsableItemFromData()
{
	TArray<FItemInformation*> Rows;
	check(ItemData);
	ItemData->GetAllRows<FItemInformation>(TEXT("ItemDataTable"), Rows);

		int32 UsableItemCount = 0;

		for (FItemInformation* Row : Rows)
		{
			if (Row->ItemType == EItemType::Usable)
			{
				UsableItemCount++;

				EItemName Name = Row->ItemName;
				float Probability = Row->Probability;
				ProbabilitySum += Probability;
				UsableItemProbabilistic.Add(Name, Probability);
			}
		}
		UsableItemTotal = UsableItemCount;
}


//-----overlapItem-----
void AInteractionItemComponent::AddOverlapItem(ABaseItem* Item)
{
	OverlapItems.Add(Item);

}

void AInteractionItemComponent::RemoveOverlapItem(ABaseItem* Item)
{
	OverlapItems.Remove(Item);
}
//-------

void AInteractionItemComponent::PickUpAnItem()
{
	if (OverlapItems.Num() > 0)
	{
		ABaseItem* PickUpItem = GetItemCloseToPlayer();
		
		if (PickUpItem->GetItemType() == EItemType::Equipment)
		{
			EItemName ItemName = PickUpItem->GetName();
			FName EquipmentItemName = EnumValueToFName(ItemName);
			AddEquipmentItem(EquipmentItemName);

			FString EquipmentName = EquipmentItemName.ToString();
			UE_LOG(LogTemp, Warning, TEXT("EquipmentItem Name : %s"), *EquipmentName);
			
		}
		else if (PickUpItem->GetItemType() == EItemType::Usable)
		{
			FName UsableItemName = GetRandomItem();
			AddUsableItem(UsableItemName);

			FString UsableName = UsableItemName.ToString();
			UE_LOG(LogTemp, Warning, TEXT("UsableItem Name : %s"), *UsableName);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ItemsComponent::PickUpAnItem : Pickupitem is null"));
		}
	}
}

void AInteractionItemComponent::AddEquipmentItem(FName ItemName)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Player = Cast<APlayerCharacter>(PlayerPawn);
	check(Player);
	HUDWidgetComponent = Player->PlayerWidget;

	if (HUDWidgetComponent)
	{
		if (!ItemList.Contains(ItemName))
		{
			ItemList.Add(ItemName, 1);
			HUDWidgetComponent->AddEquipmentItem(ItemName, GetItemTexture(ItemName));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HUD Widget is null!!!!!!!!!"));
	}

}

void AInteractionItemComponent::AddUsableItem(FName ItemName)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Player = Cast<APlayerCharacter>(PlayerPawn);
	check(Player);
	HUDWidgetComponent = Player->PlayerWidget;  
	 
	if (HUDWidgetComponent) 
	{ 
		if (ItemList.Contains(ItemName)) 
		{
			ItemList[ItemName]++;
			HUDWidgetComponent->UpdateUsableItemCount(ItemName, ItemList[ItemName]);
		}
		else
		{
			ItemList.Add(ItemName, 1);
			HUDWidgetComponent->AddUsableItem(ItemName, GetItemTexture(ItemName));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HUD Widget is null!!!!!!!!!"));
	}
}

ABaseItem* AInteractionItemComponent::GetItemCloseToPlayer()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Player = Cast<APlayerCharacter>(PlayerPawn);
	check(Player);

	ABaseItem* ClosestItemToPlayer = OverlapItems[0];

	float ClosestDistance = Player->GetDistanceTo(ClosestItemToPlayer); //#include "GameFramework/Actor.h"

	for (int i = 1; i < OverlapItems.Num(); i++) {
		ABaseItem* Item = OverlapItems[i];
		float ItemDistance = Player->GetDistanceTo(Item);
		if (ItemDistance < ClosestDistance) {
			ClosestDistance = ItemDistance;
			ClosestItemToPlayer = OverlapItems[i];
		}
	}

	return ClosestItemToPlayer;
}

FName AInteractionItemComponent::GetRandomItem()
{
	EItemName Name = GetProbabilisticItem();
	FName ItemName = EnumValueToFName(Name);
	return ItemName;
}

EItemName AInteractionItemComponent::GetProbabilisticItem()
{
	if (ProbabilitySum > 0.f)
	{
		// 구간 0 ~ ProbabilitySum-1 중 랜덤으로 숫자 하나 뽑음
		int32 RandValue = FMath::RandRange(0.f, (ProbabilitySum * 100) - 1);
		
		// 그 구간에 맞는 확률을 가진 아이템을 찾아 반환
		int32 Panel = 0.f;
		for (auto& UsableItem : UsableItemProbabilistic)
		{
			Panel += UsableItem.Value * 100;
			if (RandValue < Panel)
			{
				return UsableItem.Key;
			}
		}
	}
	else
	{
		SetUsableItemFromData();
		GetProbabilisticItem();
	}
	return EItemName();
}

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

