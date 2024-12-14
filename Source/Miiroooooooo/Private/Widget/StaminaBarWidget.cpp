// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/StaminaBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UStaminaBarWidget::SetHealthBar(float CurrentHealth, float MaxHealth)
{
	float Health = CurrentHealth / MaxHealth;
	if (HealthBar) {
		HealthBar->SetPercent(Health);
		SetHealthLabel(Health);
	}
}

void UStaminaBarWidget::SetHealthLabel(float Health)
{
	FText HealthLabel = FText::AsNumber((int)Health);
	CurrentHealthLabel->SetText(HealthLabel);
}
