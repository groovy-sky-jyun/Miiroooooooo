// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySquareWidget.h"
#include "HealthBarWidget.h"
#include "BaseTrap.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

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

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateItemCount(FName ItemName, int Count);

	UFUNCTION()
	void AddItem(FName ItemName, UTexture2D* Texture);

public:
	UPROPERTY(meta = (BindWidget))
	UHealthBarWidget* HealthBar;

	UFUNCTION(BlueprintCallable)
	void DamagedHealth(int32 Value);

private:
	UPROPERTY()
	TArray<UInventorySquareWidget*> CellWidgets;

	UPROPERTY()
	TArray<bool> IsUsed_Item;

	UPROPERTY()
	TMap<FName, int32> ItemList;

	UPROPERTY(VisibleAnywhere)
	int32 ItemCellNum = 5;

	UFUNCTION(BlueprintCallable)
	void CastHorizontalChild();

	UFUNCTION(BlueprintCallable)
	void SetInVisibleWidgets();

private:
	UPROPERTY()
	int CurrentHp = 100;
};
