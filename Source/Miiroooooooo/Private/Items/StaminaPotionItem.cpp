// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaPotionItem.h"

void AStaminaPotionItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Use Item StaminaPotion"));
}

FName AStaminaPotionItem::GetRowName()
{
	return "StaminaPotion";
}
