// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySquareWidget.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API UInventorySquareWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	class UImage* Image;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Count;

	UFUNCTION(BlueprintCallable)
	void SetVisible(bool bIsVisible);

	UFUNCTION(BlueprintCallable)
	void SetCountText(FText NewText);
};
