// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Components/HorizontalBox.h"
#include "Engine/Engine.h"

//À§Á¬ ÃÊ±âÈ­
void UInventoryWidget::NativeConstruct() {
	CastHorizontalChild();
	SetInVisibleWidgets();
}

void UInventoryWidget::CastHorizontalChild()
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

void UInventoryWidget::SetInVisibleWidgets()
{
	for (UInventorySquareWidget* Cell : CellWidgets) {
		Cell->SetVisible(false); 
	}
}

void UInventoryWidget::AddItemToInventory(int Index, int Count)
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
		UE_LOG(LogTemp, Warning, TEXT("LiquidWidgets Is Not ValidIndex : %d"), Index);
	}
}

