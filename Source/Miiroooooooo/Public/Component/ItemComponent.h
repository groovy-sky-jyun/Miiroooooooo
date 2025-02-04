// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseItem.h"
#include "ItemComponent.generated.h"

UCLASS()
class MIIROOOOOOOO_API UItemComponent : public UObject
{
	GENERATED_BODY()

public:
	UItemComponent();

public:
	UFUNCTION()
	void AddOverlapItem(ABaseItem* Item);

	UFUNCTION()
	void RemoveOverlapItem(ABaseItem* Item);

public:
	UFUNCTION()
	void PickUpAnItem();

	//È®·üÇü
	UFUNCTION()
	void GetRandomUsableItem();

	UFUNCTION()
	ABaseItem* GetItemCloseToPlayer();

public:
	UFUNCTION()
	void UseItem();

private:
	UPROPERTY()
	TArray<ABaseItem*> OverlapItems;

	UPROPERTY()
	TArray<int32> OverlapNum;

	UPROPERTY()
	int32 UsableItemTotal;

	UPROPERTY()
	TObjectPtr<class UMiirooooGameInstance> GameInstance;

	UPROPERTY()
	TObjectPtr<class APlayerCharacter> Player;
};

