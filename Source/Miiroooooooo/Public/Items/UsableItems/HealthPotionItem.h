// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
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
	virtual bool bIsAvailableItem() override;

	virtual void UseItem() override;	


private:
	UPROPERTY(VisibleAnywhere,Category = "Heal")
	float HealValue = 10.0f;


};