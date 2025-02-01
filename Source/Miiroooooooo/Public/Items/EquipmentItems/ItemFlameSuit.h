// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentItems.h"
#include "ItemFlameSuit.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API AItemFlameSuit : public AEquipmentItems
{
	GENERATED_BODY()
	
public:
	virtual void SetName() override;

	virtual FName GetName() override;

	virtual void EffectOnProssession() override;
};
