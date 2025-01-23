// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "StaminaPotionItem.h"
#include "RandomPotionItem.h"
#include "FireBombItem.h"
#include "AcidBloodItem.h"
#include "SprayItem.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	StaminaClass = GetWorld()->SpawnActor<AStaminaPotionItem>(AStaminaPotionItem::StaticClass());
	RandomClass = GetWorld()->SpawnActor<ARandomPotionItem>(ARandomPotionItem::StaticClass());
	FireBombClass = GetWorld()->SpawnActor<AFireBombItem>(AFireBombItem::StaticClass());
	AcidBloodClass = GetWorld()->SpawnActor<AAcidBloodItem>(AAcidBloodItem::StaticClass());
	SprayClass = GetWorld()->SpawnActor<ASprayItem>(ASprayItem::StaticClass());

	//PlayerCharacter의 PlayerWidget 초기화 및 가져오기
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter) {
		PlayerCharacter->SetWidgetToViewPort();
		if(PlayerCharacter->PlayerWidget)
			ItemWidget = PlayerCharacter->PlayerWidget;
	}
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/*---[Add Item]---*/
void UInventoryComponent::AddToInventory()
{
	ABasicItem* ItemClass = CloseToPlayer();
	if (ItemClass && ItemClass->ItemType == EItemType::TreasureChest) {
		
		FItemStructure ItemStructure = GetRnadItem(EItem::Liquid);
		if (&ItemStructure) {
			AddItem(ItemStructure);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("ChestItems are SoldOut"));
		}
	}
	else if (ItemClass && ItemClass->ItemType == EItemType::Wear) {
		FName RowName = ItemClass->GetRowName();
		FItemStructure* ItemStructure = ItemTable->FindRow<FItemStructure>(RowName, TEXT("RowName"));
		AddItem(*ItemStructure);
	}
}
void UInventoryComponent::AddItem(FItemStructure ItemStructure)
{
	int Index = ItemStructure.Index;

	if (!InventoryItems.Contains(Index)) {
		InventoryItems.Add(Index, 1);
		CurrentItems.Add(Index, 1);
		ItemWidget->AddItemToInventory(Index, 1);
	}
	else if (InventoryItems[Index] < ItemStructure.Count) {
		InventoryItems[Index]++;
		CurrentItems[Index]++;
		ItemWidget->AddItemToInventory(Index, CurrentItems[Index]);
	}
}
ABasicItem* UInventoryComponent::CloseToPlayer()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (OverlapItems.Num() > 0) {
		float Length = Player->GetDistanceTo(OverlapItems[0]);
		ABasicItem* ItemClass = OverlapItems[0];
		for (int i = 1; i < OverlapItems.Num(); i++) {
			float Distance = Player->GetDistanceTo(OverlapItems[i]);
			if (Distance < Length) {
				Length = Distance;
				ItemClass = OverlapItems[i];
			}
		}
		return ItemClass;
	}
	return nullptr;
}
FItemStructure UInventoryComponent::GetRnadItem(EItem ItemType)
{
	TArray<FItemStructure*> Items;
	for (auto& Row : ItemTable->GetRowMap()) {
		FItemStructure* ItemStructure = (FItemStructure*)Row.Value;
		if (ItemStructure && ItemStructure->ItemType == ItemType) {
			int Index = ItemStructure->Index;
			if ((InventoryItems.Contains(Index) && InventoryItems[Index] < ItemStructure->Count) || !InventoryItems.Contains(Index)) {
				Items.Add(ItemStructure);
			}
		}
	}
	
	if (Items.Num() > 0) {
		return *Items[FMath::RandRange(0, Items.Num() - 1)];
	}
	else {
		return FItemStructure();
	}
}
//--------------------------------

/*---[Use Item]---*/
void UInventoryComponent::PressUseItem(int KeyNum)
{
	int Index = KeyNum - 1;
	ABasicItem* ItemInstance = nullptr;

	switch (Index) {
	case 0: {
		UseItemToInventory(Index, StaminaClass);
		break;
	}
	case 1:
		UseItemToInventory(Index,RandomClass);
		break;
	case 2:
		UseItemToInventory(Index, FireBombClass);
		break;
	case 3:
		UseItemToInventory(Index, AcidBloodClass);
		break;
	case 4:
		UseItemToInventory(Index, SprayClass);
		break;
	}
}
void UInventoryComponent::UseItemToInventory(int Index, ABasicItem* ItemClass)
{
	// 플레이어가 소유하고 있는지 확인
	if (ItemClass && CurrentItems[Index] > 0) {
		// 아이템 개수 감소
		CurrentItems[Index]--;

		// 아이템 사용 효과
		ItemClass->UseItem();

		// 인벤토리 widget 아이템 개수 감소
		ItemWidget->AddItemToInventory(Index, CurrentItems[Index]);
	}
}
//--------------------------

/*--- [Overlap]---*/
void UInventoryComponent::AddOverlapItem(ABasicItem* ItemClass)
{
	OverlapItems.Add(ItemClass);
}
void UInventoryComponent::RemoveOverlapItem(ABasicItem* ItemClass)
{
	OverlapItems.Remove(ItemClass);
}//------------------------------






