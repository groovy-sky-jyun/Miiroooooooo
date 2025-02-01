// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MiirooooGameInstance.generated.h"

UENUM(BlueprintType)
enum class EItemName : uint8
{
	HealthPotion,
	RandomPotion,
	Water,
	FireBomb,
	ChainSaw,
	FlameSuit
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Equipment,
	Usable
};

USTRUCT(BlueprintType)
struct FItemInformation : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ko_ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Explanation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Probability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;
};

UCLASS()
class MIIROOOOOOOO_API UMiirooooGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMiirooooGameInstance();

	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CustomReference")
	UDataTable* ItemData;

	UFUNCTION()
	UTexture2D* GetItemTexture(FName ItemName);

	UFUNCTION()
	void SetUsableItemTotal();

	UFUNCTION()
	int32 GetUsableItemTotal();

public:
	UFUNCTION()
	void AddItem(FName ItemName);

	UFUNCTION()
	void UseItem(FName ItemName);

	UFUNCTION()
	bool HasItemInInventory(FName ItemName);

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
};
