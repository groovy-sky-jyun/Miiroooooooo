// Fill out your copyright notice in the Description page of Project Settings.


#include "MiiroooPlayerController.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"

void AMiiroooPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (InventoryWidgetClass) {
		InventoryWidgetInstance = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		if (InventoryWidgetInstance) {
			InventoryWidgetInstance->AddToViewport();
		}
	}
}

void AMiiroooPlayerController::UpdateInventoryItemImage(int Number, int Count,UTexture2D* Image)
{
	if (InventoryWidgetInstance) {
		InventoryWidgetInstance->SetInventory(Number, Count, Image);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Please Set PlayerController -> InventoryWidget Class"));
	}
}

