// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicItem.h"
#include "StaminaPotionItem.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API AStaminaPotionItem : public ABasicItem
{
	GENERATED_BODY()

public:	
	virtual void UseItem() override;
};
