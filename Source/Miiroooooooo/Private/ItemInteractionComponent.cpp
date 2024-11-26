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


// ������ �� ������ �߰�
void UItemInteractionComponent::AddOverlapItem(AActor* ItemClass)
{
	OverlapItemList.Add(ItemClass);
}

// ������ �ƾ��� ������ ����
void UItemInteractionComponent::RemoveOverlapItem(AActor* ItemClass)
{
	OverlapItemList.Remove(ItemClass);
}

// �÷��̾ FŰ�� ������ �� ������ ȹ��
void UItemInteractionComponent::AddItemToPlayer()
{
	if (OverlapItemList.Num() > 0) {
		// ȹ���� �������� Structure
		FItemStructure ItemStructure = GetItemStructure(CloseToPlayer());
		UE_LOG(LogTemp, Warning, TEXT("Obtain an Item: %s"), *FText::FromString(ItemStructure.Name).ToString());
		
		//�� ��������
		int Number = ItemStructure.Number;
		UTexture2D* Image = ItemStructure.Image; 

		//DataTable, PlayerItems Count ���� ����
		CountUpdate(Number);

		int32 Count= ItemsComponent->GetItemCount(Number);
	
		// PlayerController�� ����
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

// 1) ������ �� �����۵��� �ִ��� Ȯ��
// 2) �÷��̾�� ���� ����� ������ ��������
AActor* UItemInteractionComponent::CloseToPlayer()
{
	// �÷������� �÷��̾ ������
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	// �������� ������ �迭���� ���� ù��° �����ۿ� �÷��̾��� �Ÿ� ����
	float Length = PlayerCharacter->GetDistanceTo(OverlapItemList[0]);
	AActor* ItemClass = OverlapItemList[0];

	// interact item�� 2�� �̻��� ��� �Ÿ� ��
	// -> �÷��̾�� ���� ����� ������ ��ȯ
	for (int i = 1; i < OverlapItemList.Num(); i++) {
		float Distance = PlayerCharacter->GetDistanceTo(OverlapItemList[i]);
		if (Distance < Length) {
			Length = Distance;
			ItemClass = OverlapItemList[i];
		}
	}

	return ItemClass;
}

// ������ Ÿ�Կ� �°� Structure ��ȯ
FItemStructure UItemInteractionComponent::GetItemStructure(AActor* ItemClass)
{
	ABasicItem* BasicItem = Cast<ABasicItem>(ItemClass);
	if (BasicItem) {
		// ������ Ÿ���� Wear �� ���
		if (BasicItem->ItemType == EItemType::Wear) {
			return GetWearStructure(BasicItem);
		}
		// ������ Ÿ���� TreasureChest �� ���
		else if (BasicItem->ItemType == EItemType::TreasureChest) {
			return GetLiquidStructure();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Overlap Item Is Not BasicItemClass"));
	}

	return FItemStructure();

}

// Wear �������� ItemStructure ��ȯ
FItemStructure UItemInteractionComponent::GetWearStructure(ABasicItem* WearItem)
{
	// �ش� BP Item���� ����ڰ� ������ RowName�� �̿�
	// DataTable���� (RowName�� ��ġ && ������ 1�� �̻�) Structure�� ��ȯ	
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

// TreasureChest �������� ItemStructure ��ȯ
FItemStructure UItemInteractionComponent::GetLiquidStructure()
{
	//  DataTable ���� Liquid �� �׸�� ��������
	TArray<FItemStructure> LiquidItems = GetStructureForType(EItem::Liquid);

	if (LiquidItems.Num() > 0) {
		// Liquid ����Ʈ �� �Ѱ� ���� ��ȯ
		FItemStructure LiquidData = GetRandomStructure(LiquidItems);
		// ��ȯ�� �������� RandomPotion�� ���
		if (LiquidData.Name.Equals(TEXT("RandomPotion"))) {
			// DataTable ���� RandomPotion �� �׸�� ��������
			TArray<FItemStructure> RandomPotions = GetStructureForType(EItem::Random);
			if (RandomPotions.Num() > 0 && LiquidData.Count > 0) {
				// �� �� �������� �ϳ� ����
				return GetRandomStructure(RandomPotions);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("The Number Of RandomPotions Is Zero. Check RandomPotion Count"));
			}
		}
		else {
			// ��ȯ�� �������� RandomPotion�� �ƴ� ��� �ش� ������ ��ȯ
			return LiquidData;
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Items Sold Out. Please Check Destroy To BP_Wear"));
	}
	return FItemStructure();
}

// DataTable ���� (ItemEnum == 'ItemType' && Number�� 1�� �̻�)�� �׸�� ��������
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

// Structure ����Ʈ �� �������� �ϳ��� Structure ��ȯ
FItemStructure UItemInteractionComponent::GetRandomStructure(TArray<FItemStructure> ItemStructures)
{
	int32 ShuffleNum = FMath::RandRange(0, ItemStructures.Num() - 1);
	return FItemStructure(ItemStructures[ShuffleNum]);
}

// DataTable ������ ���� ����(����)
// ItemsComponent ������ ���� ����(����)
void UItemInteractionComponent::CountUpdate(int32 Number)
{
	ItemsComponent->AddItems(Number);

	//RandomPotion Liquid ���� ����
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

	//Item ���� ����(RandomPotion�� ��쿡�� Random Type
	for (auto& Row : ItemTable->GetRowMap()) {
		FItemStructure* RowData = (FItemStructure*)Row.Value;
		if (RowData && RowData->Number == Number && RowData->Count>0 && Number!=2) {
			int32 UpdateCount = RowData->Count - 1;
			RowData->Count = UpdateCount;
			break;
		}
	}
}



