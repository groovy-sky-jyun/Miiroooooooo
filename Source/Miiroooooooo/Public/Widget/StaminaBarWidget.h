// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaminaBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API UStaminaBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* CurrentHealthLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxHealthLabel;

	UFUNCTION(BlueprintCallable)
	void SetHealthBar(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintCallable)
	void SetHealthLabel(float Health); 



};
