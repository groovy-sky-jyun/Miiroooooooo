// Fill out your copyright notice in the Description page of Project Settings.


#include "SprayItem.h"

void ASprayItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Use Item Spray"));
}

FName ASprayItem::GetRowName()
{
	return "Sprey";
}
