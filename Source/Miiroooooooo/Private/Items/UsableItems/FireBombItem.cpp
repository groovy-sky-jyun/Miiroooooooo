// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBombItem.h"

void AFireBombItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Use Item FireBomb"));
}

void AFireBombItem::SetName()
{
	ItemName = FName("FireBomb");
}

FName AFireBombItem::GetName()
{
	return ItemName;
}

