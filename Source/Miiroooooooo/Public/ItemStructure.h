// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStructure.generated.h"

UENUM(BlueprintType)
enum class EItem : uint8
{
	Object UMETA(DisplayName = "Object"),
	Liquid UMETA(DisplayName = "Liquid"),
	Random UMETA(DisplayName = "Random")
};
USTRUCT(BlueprintType)
struct FItemStructure : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Number;
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Explanation; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Digits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItem ItemEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;


};