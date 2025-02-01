// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"
#include "SprayItem.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API ASprayItem : public AUsableItem
{
	GENERATED_BODY()
	
public:
	virtual void SetName() override;

	virtual FName GetName() override;

	virtual void UseItem() override;

	class AWall* CheckTraceWall();
};
