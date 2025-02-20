// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/UsableItems/UsableItem.h"
#include "PickaxItem.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API APickaxItem : public AUsableItem
{
	GENERATED_BODY()

public:
	virtual void SetName() override { ItemName = EItemName::Pickax; };

	virtual void UseItem() override;
};
