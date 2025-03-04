// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_HUDWidget;

	UFUNCTION()
	void ShowHUDWidget();

	UFUNCTION()
	void HideHUDWidget();


public:
	UFUNCTION()
	void AddItemToInventory(FName ItemName, UTexture2D* Texture);

	UFUNCTION()
	void UpdateItemToInventory(FName ItemName, int Count);

public:
	UFUNCTION()
	void AddHealth(int32 Value);

	UFUNCTION()
	void DamageHealth(int32 Value);


private:
	UPROPERTY()
	class UHUDWidget* HUDWidget;
};