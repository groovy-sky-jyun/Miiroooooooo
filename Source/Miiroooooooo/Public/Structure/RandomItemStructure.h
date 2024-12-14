// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RandomItemStructure.generated.h"

UENUM(BlueprintType)
enum class EType : uint8
{
	Speed UMETA(DisplayName = "Speed"),
	Hp UMETA(DisplayName = "Hp"),
	Reverse UMETA(DisplayName = "Reverse")
};
USTRUCT(BlueprintType)
struct FRandomItemStructure : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Digits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EType ItemType;
};
