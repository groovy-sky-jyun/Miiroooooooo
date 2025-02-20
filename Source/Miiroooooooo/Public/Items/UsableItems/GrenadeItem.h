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
	virtual void SetName() override { ItemName = EItemName::Grenade; };
	virtual void UseItem() override;
};
