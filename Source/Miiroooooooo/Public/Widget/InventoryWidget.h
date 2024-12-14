// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "InventorySquareWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<UInventorySquareWidget*> CellWidgets;

	UPROPERTY(meta=(BindWidget))
	class UInventorySquareWidget* ItemCell_1;

	UPROPERTY(meta = (BindWidget))
	class UInventorySquareWidget* ItemCell_2;

	UPROPERTY(meta = (BindWidget))
	class UInventorySquareWidget* ItemCell_3;

	UPROPERTY(meta = (BindWidget))
	class UInventorySquareWidget* ItemCell_4 ;

	UPROPERTY(meta = (BindWidget))
	class UInventorySquareWidget* ItemCell_5 ;

	UPROPERTY(meta = (BindWidget))
	class UInventorySquareWidget* ItemCell_6;

	UPROPERTY(meta = (BindWidget))
	class UInventorySquareWidget* ItemCell_7;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void CastHorizontalChild();

	UFUNCTION(BlueprintCallable)
	void SetInVisibleWidgets();

	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(int Index, int Count);

};
