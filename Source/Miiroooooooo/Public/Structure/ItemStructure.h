// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemStructure.generated.h"

class AUsableItem;

UENUM(BlueprintType)
enum class EItemName : uint8
{
	HealthPotion,
	RandomPotion,
	AcidBlood,
	FireBomb,
	Spray,
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

USTRUCT(BlueprintType)
struct FUsableItemClass : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AUsableItem* ItemClass;
};

UCLASS()
class MIIROOOOOOOO_API UItemStructure : public UObject
{
	GENERATED_BODY()
	
};
