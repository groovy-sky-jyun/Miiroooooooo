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

	UFUNCTION(BlueprintCallable)
	void UpdateUsableItemCount(FName ItemName, int Count);

	UFUNCTION()
	void AddUsableItem(FName ItemName, UTexture2D* Texture);

	UFUNCTION()
	void AddEquipmentItem(FName ItemName, UTexture2D* Texture);



public:
	UPROPERTY(meta = (BindWidget))
	UHealthBarWidget* HealthBar;

	//UFUNCTION(BlueprintCallable)
	//void UpdateHealth(int32 Value);

private:
	UPROPERTY()
	TArray<bool> IsUsed_UsableItem;

	UPROPERTY()
	TArray<bool> IsUsed_Equipment;

	UPROPERTY()
	TMap<FName, int32> ItemList;


	UPROPERTY(VisibleAnywhere)
	int32 UsableItemCellNum = 5;

	UPROPERTY(VisibleAnywhere)
	int32 EquipmentItemCellNum = 2;
};
