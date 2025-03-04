// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotionItem.h"
#include "MiiroooPlayerController.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"


bool AHealthPotionItem::bIsAvailableItem()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UHealthComponent* HealthComponent = PlayerCharacter->HealthComponent;
	if (!HealthComponent->bIsFullHealth())
	{
		return true;
	}
	return false;
}

void AHealthPotionItem::UseItem()
{
	AMiiroooPlayerController* PlayerController = Cast<AMiiroooPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->AddHealth(HealValue);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UHealthComponent* HealthComponent = PlayerCharacter->HealthComponent;
	HealthComponent->AddHealth(HealValue);
}

