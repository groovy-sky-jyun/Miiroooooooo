// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBarWidget::SetHealthBar(float Value)
{
	HealthBar->SetPercent(Value);
}

void UHealthBarWidget::SetHealthLabel(float Value)
{
	FText HealthLabel = FText::AsNumber((int)Value);
	CurrentHealthLabel->SetText(HealthLabel);
}
