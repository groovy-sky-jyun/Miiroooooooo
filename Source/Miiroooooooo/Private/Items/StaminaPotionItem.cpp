// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaPotionItem.h"


void AStaminaPotionItem::UseItem()
{
	if(HealthInstance)
		HealthInstance->AddStamina(HealValue);
}
