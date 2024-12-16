// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicItem.h"
#include "HealthComponent.h"
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

private:
	UPROPERTY(VisibleAnywhere)
	float HealValue = 30.0f;

	UFUNCTION(BlueprintCallable)
	void AddStamina();

	UFUNCTION(BlueprintCallable)
	void SubStamina();

	UFUNCTION(BlueprintCallable)
	void FastSpeed();

	UFUNCTION(BlueprintCallable)
	void SlowSpeed();

	UFUNCTION(BlueprintCallable)
	void ReverseKey();
};
