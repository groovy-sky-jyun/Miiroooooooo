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

/*---[초기화]---*/
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	//ChestStructureList 초기화
	GetStructuresForType(EItem::Liquid);

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
// ChestStructureList = DataTable에서 Liquid Type 아이템 Structure 복사
// DataTable값을 직접적으로 변경하지 않기 위함
void UInventoryComponent::GetStructuresForType(EItem ItemType)
{
	for (auto& Row : ItemTable->GetRowMap()) { 
		FItemStructure* ItemStructure = (FItemStructure*)Row.Value; 
		if (ItemStructure && ItemStructure->ItemType == ItemType) {
			ChestStructureList.Add(*ItemStructure);
		}
	}
}/*--------------------*/


/*---[아이템 획득]---*/
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
//오버랩 된 아이템들 중 플레이어와 가장 가까이 있는 아이템 클래스 반환
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
// ChestItem 중 랜덤 1개 개수 확인 후 Add Inventory && Update Widget
void UInventoryComponent::AddChestItem()
{
	// ChestStructureList(DataTable 복사된값) 중 아이템 개수가 1개 이상 남은것들만 모으기
	TArray<FItemStructure*> ChestList;
	for (FItemStructure& Item : ChestStructureList) {
		if (Item.Count > 0) {
			ChestList.Add(&Item);
		}
	}
	
	if (ChestList.Num() > 0) {
		int32 ShuffleNum = FMath::RandRange(0, ChestList.Num() - 1);
		FItemStructure* ChestItemStructure = ChestList[ShuffleNum]; // Chest 아이템 중 랜덤으로 1개 반환
		 
		if (ChestItemStructure) {
			//FName RowName = ChestItemStructure->Name;
			//AddItemList(ChestItemStructure->InventoryIndex, RowName); //해당 아이템 인벤토리에 추가
			//ChestItemStructure->Count--; //ChestItemStructure 해당 아이템 개수 감소
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("ChestItemStructure is null"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Chest Item is Sold out"));
	}
}
// WearItem 개수 확인 후 Add Inventory && Update Widget
void UInventoryComponent::AddWearItem(ABasicItem* WearItem)
{
	// RowName으로 DataTable에서 structure 찾기
	FName RowName = WearItem->GetRowName();
	FItemStructure WearItemStructure = *ItemTable->FindRow<FItemStructure>(RowName, TEXT("WearType"));
	
	//InventoryList에 없으면 새로 추가해준다.
	if (!InventoryList.Contains(RowName)) { 
		InventoryList.Add(RowName, 1);
		ItemWidget->AddItemToInventory(WearItemStructure.InventoryIndex, 1); //Inventory Widget count++
	}
	else {
		// (InventoryList Count < DataTable Count) -> 아이템 추가
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


/*---[아이템 사용]---*/
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
// 아이템 클래스 내의 override 함수 사용 (UItemInterface) && update widget
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
// '인벤토리 아이템 리스트'에서 사용한 아이템 개수 줄이기
void UInventoryComponent::UpdateItemList(FName RowName)
{
	if (InventoryList.Contains(RowName) && InventoryList[RowName] > 0) { 
		InventoryList[RowName]--;
	}
}/*--------------------*/


/*---[OverlapItemList 관리]---*/
//플레이어와 아이템 overlap 됐을 때 -> '오버랩 아이템 리스트'에 아이템 추가
void UInventoryComponent::AddOverlapItem(ABasicItem* ItemClass)
{
	OverlapItemList.Add(ItemClass);
}
//플레이어와 아이템 overlap 끝났을 때 -> '오버랩 아이템 리스트'에 아이템 삭제
void UInventoryComponent::RemoveOverlapItem(ABasicItem* ItemClass)
{
	OverlapItemList.Remove(ItemClass);
}/*--------------------*/



