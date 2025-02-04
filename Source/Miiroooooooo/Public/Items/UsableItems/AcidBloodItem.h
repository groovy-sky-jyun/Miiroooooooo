// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "AcidBloodItem.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API AAcidBloodItem : public AUsableItem
{
	GENERATED_BODY()
	
public:
	virtual void SetName() override { ItemName = EItemName::AcidBlood; };
	virtual void UseItem() override;
};
