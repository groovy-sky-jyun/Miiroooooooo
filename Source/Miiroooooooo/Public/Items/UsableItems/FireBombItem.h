// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "FireBombItem.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API AFireBombItem : public AUsableItem
{
	GENERATED_BODY()
public:
	virtual void SetName() override;

	virtual FName GetName() override;

	virtual void UseItem() override;
};
