// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentItems.h"
#include "ItemChainSaw.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API AItemChainSaw : public AEquipmentItems
{
	GENERATED_BODY()

public:
	virtual void SetName() override { ItemName = EItemName::ChainSaw; };

	virtual void EffectOnProssession() override;
};
