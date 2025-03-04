// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "RandomPotionItem.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API ARandomPotionItem : public AUsableItem
{
	GENERATED_BODY()
	
public:
	virtual bool bIsAvailableItem() override;

	virtual void UseItem() override;




private:
	UPROPERTY(VisibleAnywhere)
	float HealValue = 30.0f;

	UPROPERTY(VisibleAnywhere)
	float DamageValue = 30.0f;

	UFUNCTION(BlueprintCallable)
	void AddHealth();

	UFUNCTION(BlueprintCallable)
	void DamageHealth();

	UFUNCTION(BlueprintCallable)
	void FastSpeed();

	UFUNCTION(BlueprintCallable)
	void SlowSpeed();

	UFUNCTION(BlueprintCallable)
	void ReverseKey();
};
