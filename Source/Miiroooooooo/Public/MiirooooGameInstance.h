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
	virtual void Init() override;
};
