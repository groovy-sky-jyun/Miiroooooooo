// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventorySquareWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UInventorySquareWidget::SetVisible(bool bIsVisible)
{
	if (Image && Count) {
		Image->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		Count->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void UInventorySquareWidget::SetCountText(FText NewText)
{
	if (Count) {
		Count->SetText(NewText);
	}
}
