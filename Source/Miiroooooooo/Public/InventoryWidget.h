// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UImage* Item_1;

	UPROPERTY(meta=(BindWidget))
	class UImage* Item_2;

	UPROPERTY(meta = (BindWidget))
	class UImage* Item_3;

	UPROPERTY(meta = (BindWidget))
	class UImage* Item_4;

	UPROPERTY(meta = (BindWidget))
	class UImage* Item_5;

	UPROPERTY(meta = (BindWidget))
	class UImage* Item_6;

	UPROPERTY(meta = (BindWidget))
	class UImage* Item_7;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCount_1;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCount_2;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCount_3;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCount_4;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCount_5;


	//slot에 아이템 추가 및 아이템 리스트에 추가
	UFUNCTION(BlueprintCallable)
	void SetInventory(int Number, int Count, UTexture2D* Image);

	//item이 인벤토리의 몇번째 칸인지 알려줌
	UFUNCTION(BlueprintCallable)
	int32 GetItemIndexNum(FName RowName);
};
