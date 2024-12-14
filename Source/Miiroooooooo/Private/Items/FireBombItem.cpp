// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FireBombItem.h"

void AFireBombItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Use Item FireBomb"));
}

FName AFireBombItem::GetRowName()
{
	return "Firebomb";
}
