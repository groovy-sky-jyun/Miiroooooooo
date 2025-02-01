// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySquareWidget.h"
#include "HealthBarWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	int32 UsableItemCellNum = 5;

public:
	UPROPERTY(meta=(BindWidget))
	UInventorySquareWidget* ItemCell_1;

	UPROPERTY(meta = (BindWidget))
	UInventorySquareWidget* ItemCell_2;

	UPROPERTY(meta = (BindWidget))
	UInventorySquareWidget* ItemCell_3;

	UPROPERTY(meta = (BindWidget))
	UInventorySquareWidget* ItemCell_4 ;

	UPROPERTY(meta = (BindWidget))
	UInventorySquareWidget* ItemCell_5 ;

	UPROPERTY(meta = (BindWidget))
	UInventorySquareWidget* ItemCell_6;

	UPROPERTY(meta = (BindWidget))
	UInventorySquareWidget* ItemCell_7;

	UFUNCTION(BlueprintCallable)
	void CastHorizontalChild();

	UFUNCTION(BlueprintCallable)
	void SetInVisibleWidgets();

	virtual void NativeConstruct() override;
	
public:
	UPROPERTY()
	TArray<UInventorySquareWidget*> CellWidgets;

	UPROPERTY()
	TArray<FName> UsableItems;

	UPROPERTY()
	TArray<bool> IndexInUsed;

	UFUNCTION(BlueprintCallable)
	void UpdateItemToInventory(int Index, int Count);

	UFUNCTION()
	void AddUsableItem(FName ItemName, int32 Count);

	UFUNCTION()
	void UseUsableItem(FName ItemName, int32 Count);

	UFUNCTION()
	int32 FindUnUsedIndex();

	UFUNCTION()
	UTexture2D* SetInventoryTexture(FName ItemName);

public:
	UPROPERTY(meta = (BindWidget))
	UHealthBarWidget* HealthBar;

	UFUNCTION(BlueprintCallable)
	void UpdateHealth(int32 Value);
};
