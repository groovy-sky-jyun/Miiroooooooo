// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemsComponent.h"
#include "InteractionItems.generated.h"

class UsableItem;

UCLASS(Blueprintable, BlueprintType)
class MIIROOOOOOOO_API UInteractionItems : public UObject
{
	GENERATED_BODY()
	
public:
	UInteractionItems();

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite,Category="Items")
	UItemsComponent* ItemsComponent;

	UFUNCTION()
	void AddOverlapItems(AUsableItem* ItemClass);

	UFUNCTION()
	void RemoveOverlapItems(AUsableItem* ItemClass);

	UFUNCTION()
	void PickUpAnItem();

private:
	UPROPERTY()
	TArray<AUsableItem*> OverlapItems;

	UFUNCTION()
	AUsableItem* GetItemForCloseToPlayer();

	//UFUNCTION()
	//int32 GetRandomItemForTreasureChest();
};
