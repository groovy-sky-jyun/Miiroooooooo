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
#include "BaseTrap.h"
#include "Engine/World.h"
#include "EngineUtils.h"

//HUD Widget 초기화
void UHUDWidget::NativeConstruct() 
{
	CastHorizontalChild();
	SetInVisibleWidgets();

	IsUsed_Item.SetNum(ItemCellNum);

	for (TActorIterator<ABaseTrap> It(GetWorld()); It; ++It)
	{
		It->DamagedOnChange.AddUObject(this, &UHUDWidget::DamagedHealth);
	}
}

void UHUDWidget::CastHorizontalChild()
{
	if (ItemCell_1 && ItemCell_2 && ItemCell_3 && ItemCell_4 && ItemCell_5) {
		CellWidgets.Add(ItemCell_1);
		CellWidgets.Add(ItemCell_2);
		CellWidgets.Add(ItemCell_3);
		CellWidgets.Add(ItemCell_4);
		CellWidgets.Add(ItemCell_5);
	}
}

void UHUDWidget::SetInVisibleWidgets()
{
	for (UInventorySquareWidget* Cell : CellWidgets) {
		Cell->SetVisible(false); 
	}
}

void UHUDWidget::UpdateItemCount(FName ItemName, int Count)
{
	FText NewCount = FText::AsNumber(Count);
	if (ItemList.Contains(ItemName))
	{
		int32 Index = ItemList[ItemName];
		UInventorySquareWidget* CellWidget = CellWidgets[Index];
		check(CellWidget);

		if (Count > 0)
		{
			CellWidget->SetCountText(NewCount);
		}
		else //Remove로 아이템 모두 소진한 경우
		{
			IsUsed_Item[Index] = false;
			ItemList.Remove(ItemName);
			CellWidget->SetCountText(FText::AsNumber(0));
			CellWidget->SetVisible(false);
		}
	}
}

void UHUDWidget::AddItem(FName ItemName, UTexture2D* Texture)
{
	for (int32 i = 0; i < IsUsed_Item.Num(); i++)
	{
		if (!IsUsed_Item[i])
		{
			IsUsed_Item[i] = true;
			ItemList.Add(ItemName, i);

			UInventorySquareWidget* CellWidget = CellWidgets[i];
			check(CellWidget);
			CellWidget->SetTexture2D(Texture);
			CellWidget->SetCountText(FText::AsNumber(1));
			CellWidget->SetVisible(true);

			break;
		}
	}
}

void UHUDWidget::HealHealth(int32 Value)
{
	CurrentHp += Value;
	if (CurrentHp > 100)
	{
		CurrentHp = 100;
	}
	UpdateHealthBar(CurrentHp);
}

void UHUDWidget::DamagedHealth(int32 Value)
{
	CurrentHp -= Value;
	if (CurrentHp < 0)
	{
		CurrentHp = 0;
	}
	UpdateHealthBar(CurrentHp);
}

void UHUDWidget::UpdateHealthBar(int32 NewHp)
{
	HealthBar->SetHealthBar(NewHp * 0.01);
	HealthBar->SetHealthLabel(NewHp);
}
