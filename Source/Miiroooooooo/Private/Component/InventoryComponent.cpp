// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "StaminaPotionItem.h"
#include "RandomPotionItem.h"
#include "SprayItem.h"
#include "FireBombItem.h"
#include "AcidBloodItem.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

/*---[�ʱ�ȭ]---*/
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	//PlayerCharacter�� PlayerWidget �ʱ�ȭ �� ��������
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

/*---[������ ȹ��]---*/
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
		ItemWidget->AddItemToInventory(Index, 1);
	}
	else if (InventoryItems[Index] < ItemStructure.Count) {
		InventoryItems[Index]++;
		ItemWidget->AddItemToInventory(Index, InventoryItems[Index]);
	}
}

//������ �� �����۵� �� �÷��̾�� ���� ������ �ִ� ������ Ŭ���� ��ȯ
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

/*--- [OverlapItems ����]---*/
//�÷��̾�� ������ overlap ���� �� -> '������ ������ ����Ʈ'�� ������ �߰�
void UInventoryComponent::AddOverlapItem(ABasicItem* ItemClass)
{
	OverlapItems.Add(ItemClass);
}
//�÷��̾�� ������ overlap ������ �� -> '������ ������ ����Ʈ'�� ������ ����
void UInventoryComponent::RemoveOverlapItem(ABasicItem* ItemClass)
{
	OverlapItems.Remove(ItemClass);
}//--------------------


/*---[������ ���]---
void UInventoryComponent::PressUseItem(int KeyNum)
{
	switch (KeyNum) {
	case 1:
		UseItemClass(StaminaClass, KeyNum -1);
		break;
	case 2:
		UseItemClass(RandomClass, KeyNum - 1);
		break;
	case 3:
		UseItemClass(FireBombClass, KeyNum - 1);
		break;
	case 4:
		UseItemClass(AcidBloodClass, KeyNum - 1);
		break;
	case 5:
		UseItemClass(SprayClass, KeyNum - 1);
		break;
	}
}

// ������ Ŭ���� ���� override �Լ� ��� (UItemInterface) && update widget
void UInventoryComponent::UseItemClass(ABasicItem* Item, int Index)
{
	if (Item ) {
		FName RowName = Item->GetRowName();
		if (InventoryItems[RowName] > 0 && InventoryItems.Contains(RowName)) {
			/*Item->UseItem();
			UpdateItemList(RowName);
			ItemWidget->AddItemToInventory(Index, InventoryItems[RowName]);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("UseItemClass : ItemClass is null"));
	}
}
// '�κ��丮 ������ ����Ʈ'���� ����� ������ ���� ���̱�
void UInventoryComponent::UpdateItemList(FName RowName)
{
	if (InventoryItems.Contains(RowName) && InventoryItems[RowName] > 0) { 
		InventoryItems[RowName]--;
	}
}--------------------*/





