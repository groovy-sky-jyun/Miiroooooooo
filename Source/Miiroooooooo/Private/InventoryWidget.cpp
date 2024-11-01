// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Engine/Engine.h"

void UInventoryWidget::SetItemImage(UTexture2D* image)
{
	//slot�� ������ �߰� �� ������ ����Ʈ�� �߰�

	ItemList.Add(image);
	if (image) {
		//FSlateBrush Brush;
		//Brush.SetResourceObject(image);
		//Item_1->SetBrush(Brush);
		Item_1->SetBrushFromTexture(image);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("SetItemImage failed."))
	}
}
