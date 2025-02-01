// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemChainSaw.h"

void AItemChainSaw::SetName()
{
	ItemName = FName("ChainSaw");
}

FName AItemChainSaw::GetName()
{
	return ItemName;
}

void AItemChainSaw::EffectOnProssession()
{
}
