// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "MiirooooGameInstance.h"
#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

//HUD Widget 초기화
void UHUDWidget::NativeConstruct() {
	CastHorizontalChild();
	SetInVisibleWidgets();
	UpdateHealth(1.0f);

	IndexInUsed.SetNum(UsableItemCellNum);
	UsableItems.SetNum(UsableItemCellNum);
	IndexInUsed.SetNum(UsableItemCellNum);
}

void UHUDWidget::CastHorizontalChild()
{
	if (ItemCell_1 && ItemCell_2 && ItemCell_3 && ItemCell_4 && ItemCell_5 && ItemCell_6 && ItemCell_7) {
		CellWidgets.Add(ItemCell_1);
		CellWidgets.Add(ItemCell_2);
		CellWidgets.Add(ItemCell_3);
		CellWidgets.Add(ItemCell_4);
		CellWidgets.Add(ItemCell_5);
		CellWidgets.Add(ItemCell_6);
		CellWidgets.Add(ItemCell_7);
	}
}

void UHUDWidget::SetInVisibleWidgets()
{
	for (UInventorySquareWidget* Cell : CellWidgets) {
		Cell->SetVisible(false); 
	}
}

void UHUDWidget::UpdateItemToInventory(int Index, int Count)
{
	FText NewCount = FText::AsNumber(Count);

	if (CellWidgets.IsValidIndex(Index) && Count > 0) {
		UInventorySquareWidget* CellWidget = CellWidgets[Index];
		if (CellWidget) {
			CellWidget->SetVisible(true);
			CellWidget->SetCountText(NewCount);
		} 
	}
	else if (CellWidgets.IsValidIndex(Index) && Count == 0) {
		UInventorySquareWidget* CellWidget = CellWidgets[Index];
		if (CellWidget) {
			CellWidget->SetVisible(false);
			CellWidget->SetCountText(NewCount);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("HUDWidget : Is Not Valid an Item Index : %d"), Index);
	}
}

void UHUDWidget::AddUsableItem(FName ItemName, int32 Count)
{
	int32 UsedIndex = UsableItems.Find(ItemName);
	FText NewCount = FText::AsNumber(Count);

	if (UsedIndex && CellWidgets.IsValidIndex(UsedIndex))
	{
		UInventorySquareWidget* CellWidget = CellWidgets[UsedIndex];
		check(CellWidget);

		CellWidget->SetTexture2D(SetInventoryTexture(ItemName));
		CellWidget->SetCountText(NewCount);
		CellWidget->SetVisible(true);
	}
	else if(!UsedIndex)
	{
		int32 UnUsedIndex = FindUnUsedIndex();

		CellWidgets.IsValidIndex(UnUsedIndex);
		UInventorySquareWidget* CellWidget = CellWidgets[UnUsedIndex];
		check(CellWidget);
		
		// 사용중으로 변경
		IndexInUsed[UnUsedIndex] = true;
		UsableItems[UnUsedIndex] = ItemName;

		CellWidget->SetTexture2D(SetInventoryTexture(ItemName));
		CellWidget->SetCountText(NewCount);
		CellWidget->SetVisible(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUDWidget::AddUsableItem : CellWidget is null"));
	}
}

void UHUDWidget::UseUsableItem(FName ItemName, int32 Count)
{
	int32 UsableIndex = UsableItems.Find(ItemName);
	FText NewCount = FText::AsNumber(Count);

	if (UsableIndex && CellWidgets.IsValidIndex(UsableIndex))
	{
		UInventorySquareWidget* CellWidget = CellWidgets[UsableIndex];
		check(CellWidget);

		if (Count > 0)
		{
			CellWidget->SetCountText(NewCount);
		}
		else
		{
			CellWidget->SetVisible(false);
			IndexInUsed[UsableIndex] = false;
			UsableItems[UsableIndex] = "";
		}
	}
}

int32 UHUDWidget::FindUnUsedIndex()
{
	for (int32 index = 0; index < IndexInUsed.Num(); index++)
	{
		if (!IndexInUsed[index])
		{
			return index;
		}
	}
	return -1;
}

UTexture2D* UHUDWidget::SetInventoryTexture(FName ItemName)
{
	UGameInstance* BaseGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UMiirooooGameInstance* GameInstance = Cast<UMiirooooGameInstance>(BaseGameInstance);
	check(GameInstance);
	return GameInstance->GetItemTexture(ItemName);
}

void UHUDWidget::UpdateHealth(int32 Value)
{
	if (HealthBar) {
		HealthBar->SetHealthBar(Value);
		HealthBar->SetHealthLabel(Value*100);
	}
}

