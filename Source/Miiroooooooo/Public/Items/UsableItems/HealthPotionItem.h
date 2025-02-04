// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "HealthComponent.h"
#include "HealthPotionItem.generated.h"

class HealthComponent;
/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API AHealthPotionItem : public AUsableItem
{
	GENERATED_BODY()

public:
	virtual void SetName() override { ItemName = EItemName::HealthPotion; };

	virtual void UseItem() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	float HealValue = 15.0f;


};