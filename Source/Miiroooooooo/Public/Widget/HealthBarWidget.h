// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class MIIROOOOOOOO_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* CurrentHealthLabel;

	UFUNCTION(BlueprintCallable)
	void SetHealthBar(float Value);

	UFUNCTION(BlueprintCallable)
	void SetHealthLabel(float Value);



};
