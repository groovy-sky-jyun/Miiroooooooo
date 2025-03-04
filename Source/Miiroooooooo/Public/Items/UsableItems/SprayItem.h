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
	virtual void UseItem() override;
	virtual bool bIsAvailableItem() override;
	void DrawSpray();

private:
	// Hit result
	UPROPERTY()
	FHitResult HitResult;
	
	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FVector EndLocation;
};
