// Fill out your copyright notice in the Description page of Project Settings.


#include "MiiroooPlayerController.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"

void AMiiroooPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (InventoryWidgetClass) {
		InventoryWidgetInstance = CreateWidget<UInventoryWidget>(this, InventoryWidgetClass);
		InventoryWidgetInstance->AddToViewport();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("InventoryWidgetClass is not set"))
	}

	
}

void AMiiroooPlayerController::UpdateInventoryItemImage(UTexture2D* NewImage)
{
	if (InventoryWidgetInstance) {
		InventoryWidgetInstance->SetItemImage(NewImage);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("InventoryWidgetInstance is null"))
	}
}

