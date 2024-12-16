// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BasicItem.h"
#include "AcidBloodItem.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API AAcidBloodItem : public ABasicItem
{
	GENERATED_BODY()
	
public:
	virtual void UseItem() override;
	virtual void SetRowName() override;
};
