// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "HealthComponent.h"
#include "RandomPotionItem.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API ARandomPotionItem : public AUsableItem
{
	GENERATED_BODY()
	
public:
	virtual void SetName() override;

	virtual FName GetName() override;

	virtual void UseItem() override;

private:
	UPROPERTY(VisibleAnywhere)
	float HealValue = 30.0f;

	UFUNCTION(BlueprintCallable)
	void AddHealth();

	UFUNCTION(BlueprintCallable)
	void SubHealth();

	UFUNCTION(BlueprintCallable)
	void FastSpeed();

	UFUNCTION(BlueprintCallable)
	void SlowSpeed();

	UFUNCTION(BlueprintCallable)
	void ReverseKey();
};
