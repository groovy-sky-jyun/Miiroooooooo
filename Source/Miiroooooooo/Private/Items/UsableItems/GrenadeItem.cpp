// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeItem.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

bool AGrenadeItem::bIsAvailableItem()
{
	return true;
}

void AGrenadeItem::UseItem()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	check(PlayerPawn);

	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerPawn);
	check(Player);

	Player->bIsUsedGrenade = true;
	Player->Throwing();

	UE_LOG(LogTemp, Warning, TEXT("Use Item Grenade"));
}
