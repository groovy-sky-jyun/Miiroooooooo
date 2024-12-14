// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStructure.generated.h"

UENUM(BlueprintType)
enum class EItem : uint8
{
	Object UMETA(DisplayName = "Object"),
	Liquid UMETA(DisplayName = "Liquid")
};
USTRUCT(BlueprintType)
struct FItemStructure : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// 0부터 시작, Inventory 칸 위치 나타냄
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InventoryIndex;
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KORName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Explanation; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Digits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItem ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;


};