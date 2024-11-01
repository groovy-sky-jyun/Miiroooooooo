// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	//현재 캐릭터가 보유하고 있는 아이템 리스트
	UPROPERTY(EditAnywhere, blueprintReadWrite, Category="Inventory")
	TArray<UTexture2D*> ItemList;

	//slot에 아이템 추가 및 아이템 리스트에 추가
	UFUNCTION(BlueprintCallable)
	void SetItemImage(UTexture2D* image);
};
