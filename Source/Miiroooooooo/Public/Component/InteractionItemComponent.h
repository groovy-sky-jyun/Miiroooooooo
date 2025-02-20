// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.h"
#include "InteractionItemComponent.generated.h"

class UHUDWidget;

UCLASS()
class MIIROOOOOOOO_API AInteractionItemComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionItemComponent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	UFUNCTION()
	void OverlapItem();

	UFUNCTION()
	void UnOverlapItem();

	UFUNCTION()
	void PickUpAnItem();

	UFUNCTION()
	void PressUseItem(int KeyNum);


private:
	UPROPERTY()
	bool bIsOverlapItem;

	UPROPERTY(VisibleAnywhere, Category = "CustomReference")
	UDataTable* ItemData;

	UPROPERTY(VisibleAnywhere, Category = "CustomReference")
	UHUDWidget* HUDWidgetComponent;

	UFUNCTION()
	void SetItemData();

	UPROPERTY()
	int32 ItemTotal;

	UPROPERTY()
	TObjectPtr<class APlayerCharacter> Player;

	UPROPERTY(VisibleAnywhere)
	TMap<EItemName, float> ItemProbabilisticInfo; //<¾ÆÀÌÅÛÀÌ¸§,È®·ü>

	UPROPERTY(VisibleAnywhere)
	float ProbabilitySum; //È®·üÇÕ

	UFUNCTION()
	EItemName GetRandomItem();

	UFUNCTION()
	void AddItem(FName ItemName);

	UFUNCTION()
	UTexture2D* GetItemTexture(FName ItemName);

	UFUNCTION()
	FName EnumValueToFName(EItemName Value);


private:
	UPROPERTY()
	int32 InventoryTotal=5;

	UPROPERTY()
	TArray<bool> bIsUsedInventory;

	UPROPERTY()
	TArray<FName> ItemInventory;

	UPROPERTY(VisibleAnywhere)
	TMap<FName, int32> OwnItemList;
};
