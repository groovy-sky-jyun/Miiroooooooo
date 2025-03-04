// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeItem.h"

bool AGrenadeItem::bIsAvailableItem()
{
	return true;
}

void AGrenadeItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Use Item Grenade"));
}
