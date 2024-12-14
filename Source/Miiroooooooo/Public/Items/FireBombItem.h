// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BasicItem.h"
#include "FireBombItem.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API AFireBombItem : public ABasicItem
{
	GENERATED_BODY()
public:
	virtual void UseItem() override;
	virtual FName GetRowName() override;
};
