// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UsableItem.h"
#include "HUDWidget.h"
#include "ItemsComponent.generated.h"

class ABaseItem;


UCLASS()
class MIIROOOOOOOO_API UItemsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

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
	UPROPERTY(VisibleAnywhere)
	TArray<ABaseItem*> OverlapItems;

	UPROPERTY(VisibleAnywhere)
	int32 UsableItemTotal;

	UPROPERTY()
	TObjectPtr<class UMiirooooGameInstance> GameInstance;

	UPROPERTY()
	TObjectPtr<class APlayerCharacter> Player;
};
