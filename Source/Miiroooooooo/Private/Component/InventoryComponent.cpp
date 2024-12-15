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

	//ChestStructureList �ʱ�ȭ
	GetStructuresForType(EItem::Liquid);

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
// ChestStructureList = DataTable���� Liquid Type ������ Structure ����
// DataTable���� ���������� �������� �ʱ� ����
void UInventoryComponent::GetStructuresForType(EItem ItemType)
{
	for (auto& Row : ItemTable->GetRowMap()) { 
		FItemStructure* ItemStructure = (FItemStructure*)Row.Value; 
		if (ItemStructure && ItemStructure->ItemType == ItemType) {
			ChestStructureList.Add(*ItemStructure);
		}
	}
}/*--------------------*/


/*---[������ ȹ��]---*/
void UInventoryComponent::AddItemToInventory()
{
	ABasicItem* ItemClass = CloseToPlayer();
	if (ItemClass) {
		if (ItemClass->ItemType == EItemType::TreasureChest) {
			AddChestItem();
		}
		else if (ItemClass->ItemType == EItemType::Wear) {
			AddWearItem(ItemClass);
		}
	}
}
//������ �� �����۵� �� �÷��̾�� ���� ������ �ִ� ������ Ŭ���� ��ȯ
ABasicItem* UInventoryComponent::CloseToPlayer()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (OverlapItemList.Num() > 0) {
		float Length = Player->GetDistanceTo(OverlapItemList[0]);
		ABasicItem* ItemClass = OverlapItemList[0];
		for (int i = 1; i < OverlapItemList.Num(); i++) {
			float Distance = Player->GetDistanceTo(OverlapItemList[i]);
			if (Distance < Length) {
				Length = Distance;
				ItemClass = OverlapItemList[i];
			}
		}
		return ItemClass;
	}
	UE_LOG(LogTemp, Warning, TEXT("Overlap Item is null"));
	return nullptr;
}
// ChestItem �� ���� 1�� ���� Ȯ�� �� Add Inventory && Update Widget
void UInventoryComponent::AddChestItem()
{
	// ChestStructureList(DataTable ����Ȱ�) �� ������ ������ 1�� �̻� �����͵鸸 ������
	TArray<FItemStructure*> ChestList;
	for (FItemStructure& Item : ChestStructureList) {
		if (Item.Count > 0) {
			ChestList.Add(&Item);
		}
	}
	
	if (ChestList.Num() > 0) {
		int32 ShuffleNum = FMath::RandRange(0, ChestList.Num() - 1);
		FItemStructure* ChestItemStructure = ChestList[ShuffleNum]; // Chest ������ �� �������� 1�� ��ȯ
		 
		if (ChestItemStructure) {
			//FName RowName = ChestItemStructure->Name;
			//AddItemList(ChestItemStructure->InventoryIndex, RowName); //�ش� ������ �κ��丮�� �߰�
			//ChestItemStructure->Count--; //ChestItemStructure �ش� ������ ���� ����
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("ChestItemStructure is null"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Chest Item is Sold out"));
	}
}
// WearItem ���� Ȯ�� �� Add Inventory && Update Widget
void UInventoryComponent::AddWearItem(ABasicItem* WearItem)
{
	// RowName���� DataTable���� structure ã��
	FName RowName = WearItem->GetRowName();
	FItemStructure WearItemStructure = *ItemTable->FindRow<FItemStructure>(RowName, TEXT("WearType"));
	
	//InventoryList�� ������ ���� �߰����ش�.
	if (!InventoryList.Contains(RowName)) { 
		InventoryList.Add(RowName, 1);
		ItemWidget->AddItemToInventory(WearItemStructure.InventoryIndex, 1); //Inventory Widget count++
	}
	else {
		// (InventoryList Count < DataTable Count) -> ������ �߰�
		if (InventoryList[RowName] < WearItemStructure.Count) {
			AddItemList(WearItemStructure.InventoryIndex, RowName);
		}
	}
}
// InventoryList count++ & Inventory Widget Update
void UInventoryComponent::AddItemList(int InventoryIndex, FName RowName)
{
	if (InventoryList.Contains(RowName)) {
		InventoryList[RowName]++;
		ItemWidget->AddItemToInventory(InventoryIndex, InventoryList[RowName]); //Inventory Widget count++
	}
	else {
		InventoryList.Add(RowName, 1);
		ItemWidget->AddItemToInventory(InventoryIndex, 1); //Inventory Widget count++
	}
	FString ItemName = RowName.ToString();
}/*--------------------*/


/*---[������ ���]---*/
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
		if (InventoryList[RowName] > 0 && InventoryList.Contains(RowName)) {
			/*Item->UseItem();
			UpdateItemList(RowName);
			ItemWidget->AddItemToInventory(Index, InventoryList[RowName]);*/
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("UseItemClass : ItemClass is null"));
	}
}
// '�κ��丮 ������ ����Ʈ'���� ����� ������ ���� ���̱�
void UInventoryComponent::UpdateItemList(FName RowName)
{
	if (InventoryList.Contains(RowName) && InventoryList[RowName] > 0) { 
		InventoryList[RowName]--;
	}
}/*--------------------*/


/*---[OverlapItemList ����]---*/
//�÷��̾�� ������ overlap ���� �� -> '������ ������ ����Ʈ'�� ������ �߰�
void UInventoryComponent::AddOverlapItem(ABasicItem* ItemClass)
{
	OverlapItemList.Add(ItemClass);
}
//�÷��̾�� ������ overlap ������ �� -> '������ ������ ����Ʈ'�� ������ ����
void UInventoryComponent::RemoveOverlapItem(ABasicItem* ItemClass)
{
	OverlapItemList.Remove(ItemClass);
}/*--------------------*/



