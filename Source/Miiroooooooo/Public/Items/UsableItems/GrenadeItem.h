// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "GrenadeItem.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API AGrenadeItem : public AUsableItem
{
	GENERATED_BODY()

public:
	virtual bool bIsAvailableItem() override;

	virtual void UseItem() override;
};
