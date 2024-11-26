// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BasicItem.h"
#include "ItemStructure.h"
#include "MiiroooPlayerController.h"
#include "ItemsComponent.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UItemInteractionComponent::UItemInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UItemInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter) {
		ItemsComponent = PlayerCharacter->FindComponentByClass<UItemsComponent>();
	}
	
}


// Called every frame
void UItemInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


// 오버랩 된 아이템 추가
void UItemInteractionComponent::AddOverlapItem(AActor* ItemClass)
{
	OverlapItemList.Add(ItemClass);
}

// 오버랩 됐었던 아이템 삭제
void UItemInteractionComponent::RemoveOverlapItem(AActor* ItemClass)
{
	OverlapItemList.Remove(ItemClass);
}

// 플레이어가 F키를 눌렀을 때 아이템 획득
void UItemInteractionComponent::AddItemToPlayer()
{
	if (OverlapItemList.Num() > 0) {
		// 획득한 아이템의 Structure
		FItemStructure ItemStructure = GetItemStructure(CloseToPlayer());
		UE_LOG(LogTemp, Warning, TEXT("Obtain an Item: %s"), *FText::FromString(ItemStructure.Name).ToString());
		
		//값 가져오기
		int Number = ItemStructure.Number;
		UTexture2D* Image = ItemStructure.Image; 

		//DataTable, PlayerItems Count 개수 변경
		CountUpdate(Number);

		int32 Count= ItemsComponent->GetItemCount(Number);
	
		// PlayerController에 전달
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController) {
			AMiiroooPlayerController* MiiroooPlayerController = Cast<AMiiroooPlayerController>(PlayerController);
			if (MiiroooPlayerController) {
				UE_LOG(LogTemp, Warning, TEXT("Item Number[%d] is Set Count[%d]"), Number, Count);
				MiiroooPlayerController->UpdateInventoryItemImage(Number, Count, Image);
			}
		}
	}
}

// 1) 오버랩 된 아이템들이 있는지 확인
// 2) 플레이어와 가장 가까운 아이템 가져오기
AActor* UItemInteractionComponent::CloseToPlayer()
{
	// 플레이중인 플레이어를 가져옴
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	// 오버랩된 아이템 배열에서 가장 첫번째 아이템와 플레이어의 거리 저장
	float Length = PlayerCharacter->GetDistanceTo(OverlapItemList[0]);
	AActor* ItemClass = OverlapItemList[0];

	// interact item이 2개 이상일 경우 거리 비교
	// -> 플레이어와 가장 가까운 아이템 반환
	for (int i = 1; i < OverlapItemList.Num(); i++) {
		float Distance = PlayerCharacter->GetDistanceTo(OverlapItemList[i]);
		if (Distance < Length) {
			Length = Distance;
			ItemClass = OverlapItemList[i];
		}
	}

	return ItemClass;
}

// 아이템 타입에 맞게 Structure 반환
FItemStructure UItemInteractionComponent::GetItemStructure(AActor* ItemClass)
{
	ABasicItem* BasicItem = Cast<ABasicItem>(ItemClass);
	if (BasicItem) {
		// 아이템 타입이 Wear 인 경우
		if (BasicItem->ItemType == EItemType::Wear) {
			return GetWearStructure(BasicItem);
		}
		// 아이템 타입이 TreasureChest 인 경우
		else if (BasicItem->ItemType == EItemType::TreasureChest) {
			return GetLiquidStructure();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Overlap Item Is Not BasicItemClass"));
	}

	return FItemStructure();

}

// Wear 아이템의 ItemStructure 반환
FItemStructure UItemInteractionComponent::GetWearStructure(ABasicItem* WearItem)
{
	// 해당 BP Item에서 사용자가 지정한 RowName을 이용
	// DataTable에서 (RowName이 일치 && 개수가 1개 이상) Structure을 반환	
	FName RowName = WearItem->RowName;
	if (RowName != "") {
		FItemStructure* ItemData = ItemTable->FindRow<FItemStructure>(RowName, TEXT("Wear Type"));
		if (ItemData && ItemData->Count > 0) {
			return *ItemData;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Items Sold Out. Please Check Destroy To BP_Wear"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Please Write WearItem Details : RowName"));
	}
	return FItemStructure();
}

// TreasureChest 아이템의 ItemStructure 반환
FItemStructure UItemInteractionComponent::GetLiquidStructure()
{
	//  DataTable 에서 Liquid 인 항목들 가져오기
	TArray<FItemStructure> LiquidItems = GetStructureForType(EItem::Liquid);

	if (LiquidItems.Num() > 0) {
		// Liquid 리스트 중 한개 랜덤 반환
		FItemStructure LiquidData = GetRandomStructure(LiquidItems);
		// 반환된 아이템이 RandomPotion인 경우
		if (LiquidData.Name.Equals(TEXT("RandomPotion"))) {
			// DataTable 에서 RandomPotion 인 항목들 가져오기
			TArray<FItemStructure> RandomPotions = GetStructureForType(EItem::Random);
			if (RandomPotions.Num() > 0 && LiquidData.Count > 0) {
				// 그 중 랜덤으로 하나 추출
				return GetRandomStructure(RandomPotions);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("The Number Of RandomPotions Is Zero. Check RandomPotion Count"));
			}
		}
		else {
			// 반환된 아이템이 RandomPotion이 아닌 경우 해당 아이템 반환
			return LiquidData;
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Items Sold Out. Please Check Destroy To BP_Wear"));
	}
	return FItemStructure();
}

// DataTable 에서 (ItemEnum == 'ItemType' && Number가 1개 이상)인 항목들 가져오기
TArray<FItemStructure> UItemInteractionComponent::GetStructureForType(EItem ItemType)
{
	TArray<FItemStructure> ItemStructureList;
	for (auto& Row : ItemTable->GetRowMap()) {
		FItemStructure* RowData = (FItemStructure*)Row.Value;
		if (RowData && RowData->ItemEnum == ItemType && RowData->Count > 0) {
			ItemStructureList.Add(*RowData);
		}
	}

	if (ItemStructureList.Num() > 0) {
		return ItemStructureList;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Items Sold Out. Please Check Items Count"));
	}

	return TArray<FItemStructure>();
}

// Structure 리스트 중 랜덤으로 하나의 Structure 반환
FItemStructure UItemInteractionComponent::GetRandomStructure(TArray<FItemStructure> ItemStructures)
{
	int32 ShuffleNum = FMath::RandRange(0, ItemStructures.Num() - 1);
	return FItemStructure(ItemStructures[ShuffleNum]);
}

// DataTable 아이템 개수 변경(감소)
// ItemsComponent 아이템 개수 변경(증가)
void UItemInteractionComponent::CountUpdate(int32 Number)
{
	ItemsComponent->AddItems(Number);

	//RandomPotion Liquid 개수 감소
	if (Number >= 8 && Number <= 12) {
		for (auto& Row : ItemTable->GetRowMap()) {
			FItemStructure* RowData = (FItemStructure*)Row.Value;
			if (RowData && RowData->Number == 2 && RowData->Count > 0) {
				int32 UpdateCount = RowData->Count - 1;
				RowData->Count = UpdateCount;
				break;
			}
		}
	}

	//Item 개수 감소(RandomPotion일 경우에는 Random Type
	for (auto& Row : ItemTable->GetRowMap()) {
		FItemStructure* RowData = (FItemStructure*)Row.Value;
		if (RowData && RowData->Number == Number && RowData->Count>0 && Number!=2) {
			int32 UpdateCount = RowData->Count - 1;
			RowData->Count = UpdateCount;
			break;
		}
	}
}



