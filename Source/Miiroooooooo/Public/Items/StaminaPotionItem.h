// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicItem.h"
#include "HealthComponent.h"
#include "StaminaPotionItem.generated.h"

class HealthComponent;
/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API AStaminaPotionItem : public ABasicItem
{
	GENERATED_BODY()

public:
	virtual void UseItem() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	float HealValue = 15.0f;


};