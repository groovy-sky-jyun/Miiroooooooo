// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemFlameSuit.h"

void AItemFlameSuit::SetName()
{
	ItemName = FName("FlameSuit");
}

FName AItemFlameSuit::GetName()
{
	return ItemName;
}

void AItemFlameSuit::EffectOnProssession()
{
}
