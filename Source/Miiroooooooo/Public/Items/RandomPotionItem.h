// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicItem.h"
#include "RandomPotionItem.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API ARandomPotionItem : public ABasicItem
{
	GENERATED_BODY()
	
public:
	virtual void UseItem() override;
	virtual FName GetRowName() override;
};
