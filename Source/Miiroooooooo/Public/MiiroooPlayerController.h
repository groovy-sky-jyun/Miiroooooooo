// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InventoryWidget.h"
#include "MiiroooPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API AMiiroooPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    TSubclassOf<UInventoryWidget> InventoryWidgetClass;

    UInventoryWidget* InventoryWidgetInstance;

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateInventoryItemImage(UTexture2D* NewImage);

};