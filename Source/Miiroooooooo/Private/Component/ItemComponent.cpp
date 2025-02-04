// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PlayerCharacter.h"
#include "MiirooooGameInstance.h"
#include "BaseItem.h"
#include "UsableItem.h"
#include "ItemStructure.h"

UItemComponent::UItemComponent()
{
	OverlapItems.Empty();
}

void UItemComponent::AddOverlapItem(ABaseItem* Item)
{
	OverlapItems.Add(Item);
}

void UItemComponent::RemoveOverlapItem(ABaseItem* Item)
{
	OverlapItems.Remove(Item);
}

void UItemComponent::PickUpAnItem()
{
	UGameInstance* BaseGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	GameInstance = Cast<UMiirooooGameInstance>(BaseGameInstance);
	check(GameInstance);

	if (OverlapItems.Num() > 0)
	{
		ABaseItem* PickUpItem = GetItemCloseToPlayer();
		if (PickUpItem->GetItemType() == EItemType::Equipment)
		{
			//PickUpItem->GetName();
			//델리게이트 실행
		}
		else if (PickUpItem->GetItemType() == EItemType::Usable)
		{
			AUsableItem* ItemClass = GameInstance->GetRandomItem();
			GameInstance->AddItem(ItemClass->GetFName());
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ItemsComponent::PickUpAnItem : Pickupitem is null"));
		}
	}
}

//확률형
void UItemComponent::GetRandomUsableItem()
{
	//UsableItemTotal개수만큼 확률형 아이템 뽑기 반환
}

ABaseItem* UItemComponent::GetItemCloseToPlayer()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Player = Cast<APlayerCharacter>(PlayerPawn);
	check(Player);

	ABaseItem* ClosestItemToPlayer = OverlapItems[0];
	float ClosestDistance = Player->GetDistanceTo(ClosestItemToPlayer);

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

void UItemComponent::UseItem()
{
}
