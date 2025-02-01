// Fill out your copyright notice in the Description page of Project Settings.


#include "AcidBloodItem.h"

void AAcidBloodItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Use Item AcidBlood"));
}

void AAcidBloodItem::SetName()
{
	ItemName = FName("AcidBlood");
}

FName AAcidBloodItem::GetName()
{
	return ItemName;
}

