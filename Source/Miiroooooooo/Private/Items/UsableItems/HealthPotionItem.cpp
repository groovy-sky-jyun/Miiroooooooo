// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotionItem.h"


void AHealthPotionItem::UseItem()
{
}

void AHealthPotionItem::SetName()
{
	ItemName = FName("HealthPotion");
}

FName AHealthPotionItem::GetName()
{
	return ItemName;
}
