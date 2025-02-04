// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MiirooooGameInstance.generated.h"

class AUsableItem;

UCLASS()
class MIIROOOOOOOO_API UMiirooooGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMiirooooGameInstance();

	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CustomReference")
	UDataTable* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomReference")
	UDataTable* ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomReference")
	UUserWidget* HUDWidgetComponent;

	UFUNCTION()
	UTexture2D* GetItemTexture(FName ItemName);

	UFUNCTION()
	void SetUsableItemFromData();

	UFUNCTION()
	int32 GetUsableItemTotal();

public:
	UFUNCTION()
	void AddItem(FName ItemName);

	UFUNCTION()
	void UseItem(FName ItemName);

	UFUNCTION()
	bool HasItemInInventory(FName ItemName);

	UFUNCTION()
	AUsableItem* GetRandomItem();

	UFUNCTION()
	EItemName GetProbabilisticItem();

public:
	UFUNCTION()
	void IncreasePlayerHealth(int32 Value);

	UFUNCTION()
	void DecreasePlayerHealth(int32 Value);

	UFUNCTION()
	int32 GetPlayerHealth();

	UFUNCTION()
	bool IsHealthFull();

private:
	UPROPERTY(VisibleAnywhere)
	TMap<FName, int32> ItemList;

	UPROPERTY()
	int32 PlayerHealth=100;

	UPROPERTY(VisibleAnywhere)
	int32 UsableItemTotal;

	UPROPERTY(VisibleAnywhere)
	TMap<EItemName,float> UsableItemProbabilistic;

	UPROPERTY(VisibleAnywhere)
	float ProbabilitySum;
};
