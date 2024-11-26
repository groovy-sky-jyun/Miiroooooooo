// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Engine/Engine.h"


void UInventoryWidget::SetInventory(int Number, int Count, UTexture2D* Image)
{
	if (Number >= 8 && Number <= 12)
		Number = 2;

	switch (Number) {
	case 1: 
		if (Item_1) {
			Item_1->SetBrushFromTexture(Image);
			ItemCount_1->SetText(FText::AsNumber(Count));
			UE_LOG(LogTemp, Warning, TEXT("Add Item [%s] Image Path: %s"),*Image->GetName(), *Image->GetPathName());
		}
		break;
	case 2:
		if (Item_2) {
			Item_2->SetBrushFromTexture(Image);
			ItemCount_2->SetText(FText::AsNumber(Count));
			UE_LOG(LogTemp, Warning, TEXT("Add Item [%s] Image Path: %s"), *Image->GetName(), *Image->GetPathName());
		}
		break;
	case 3:
		if (Item_3) {
			Item_3->SetBrushFromTexture(Image);
			ItemCount_3->SetText(FText::AsNumber(Count));
			UE_LOG(LogTemp, Warning, TEXT("Add Item [%s] Image Path: %s"), *Image->GetName(), *Image->GetPathName());
		}
		break;
	case 4:
		if (Item_4) {
			Item_4->SetBrushFromTexture(Image);
			ItemCount_4->SetText(FText::AsNumber(Count));
			UE_LOG(LogTemp, Warning, TEXT("Add Item [%s] Image Path: %s"), *Image->GetName(), *Image->GetPathName());
		}
		break;
	case 5:
		if (Item_5) {
			Item_5->SetBrushFromTexture(Image);
			ItemCount_5->SetText(FText::AsNumber(Count));
			UE_LOG(LogTemp, Warning, TEXT("Add Item [%s] Image Path: %s"), *Image->GetName(), *Image->GetPathName());
		}
		break;
	case 6:
		if(Item_6)
			Item_6->SetBrushFromTexture(Image);
			UE_LOG(LogTemp, Warning, TEXT("Add Item [%s] Image Path: %s"), *Image->GetName(), *Image->GetPathName());
		break;
	case 7:
		if(Item_7)
			Item_7->SetBrushFromTexture(Image);
			UE_LOG(LogTemp, Warning, TEXT("Add Item [%s] Image Path: %s"), *Image->GetName(), *Image->GetPathName());
		break;
	}
}

int32 UInventoryWidget::GetItemIndexNum(FName RowName)
{

	return int32();
}
