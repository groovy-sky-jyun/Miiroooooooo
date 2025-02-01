// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InteractionItems.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"


UInteractionItems::UInteractionItems()
{

}
/*----- [Overlap] -----*/
void UInteractionItems::AddOverlapItems(AUsableItem* ItemClass)
{
	OverlapItems.Add(ItemClass);
}

void UInteractionItems::RemoveOverlapItems(AUsableItem* ItemClass)
{
	OverlapItems.Remove(ItemClass);
}
//------------------------------

/*----- [Add Item] -----*/
void UInteractionItems::PickUpAnItem()
{
	AUsableItem* ItemClass = GetItemForCloseToPlayer();
	/*AWearItemBasic* WearItemClass = Cast<AWearItemBasic>(ItemClass);
	
	if (WearItemClass) //ItemType::Wear
	{
		int32 ItemIndex = ItemClass->GetIndex();
		ItemsComponent->AddItem(ItemIndex);
	}
	else //ItemType::TreasureChest
	{
		int32 ItemIndex = GetRandomItemForTreasureChest();
		if (ItemIndex > 0)
		{
			ItemsComponent->AddItem(ItemIndex);
		}
	}*/
}
// Get Item From OverlapItems
AUsableItem* UInteractionItems::GetItemForCloseToPlayer()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	check(PlayerPawn);
	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerPawn);
	check(Player);

	if (OverlapItems.Num() > 0) {
		AActor* FirstUsableItem = Cast<AActor>(OverlapItems[0]);
		float Length = Player->GetDistanceTo(FirstUsableItem);

		AUsableItem* ItemClass = Cast<AUsableItem>(OverlapItems[0]);

		for (int i = 1; i < OverlapItems.Num(); i++) {
			AActor* LaterUsableItem = Cast<AActor>(OverlapItems[i]);
			float Distance = Player->GetDistanceTo(LaterUsableItem);
			if (Distance < Length) {
				Length = Distance;
				ItemClass = OverlapItems[i];
			}
		}
		return ItemClass;
	}
	return nullptr;
}
/*Get Random Item Idex from Addable Items
int32 UInteractionItems::GetRandomItemForTreasureChest()
{
	/TArray<int32> AddableItems = ItemsComponent->GetArrayOfAddableItems();
	if (AddableItems.Num() > 0)
	{
		return FMath::RandRange(0, AddableItems.Num() - 1);
	}
	else
	{
		return -1;
	}
}
//--------------------------------*/