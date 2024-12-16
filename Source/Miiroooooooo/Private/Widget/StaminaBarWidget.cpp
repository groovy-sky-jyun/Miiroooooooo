// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/StaminaBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UStaminaBarWidget::SetHealthBar(float Value)
{
	HealthBar->SetPercent(Value);
}

void UStaminaBarWidget::SetHealthLabel(float Value)
{
	FText HealthLabel = FText::AsNumber((int)Value);
	CurrentHealthLabel->SetText(HealthLabel);
}
