// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomPotionItem.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void ARandomPotionItem::UseItem()
{
	int Value = FMath::RandRange(0, 4);
	switch (Value) {
	case 0:
		AddStamina();
		break;
	case 1:
		SubStamina();
		break;
	case 2:
		FastSpeed();
		break;
	case 3:
		SlowSpeed();
		break;
	case 4:
		ReverseKey();
		break;
	}

}

void ARandomPotionItem::AddStamina()
{
	if (HealthInstance)
		HealthInstance->AddStamina(HealValue);
	UE_LOG(LogTemp, Warning, TEXT("Random Potion : Add Stamina"));
}

void ARandomPotionItem::SubStamina()
{
	if (HealthInstance)
		HealthInstance->SubStamina(HealValue);
	UE_LOG(LogTemp, Warning, TEXT("Random Potion : Sub Stamina"));
}

void ARandomPotionItem::FastSpeed()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->SetSpeed(850.0f);
	UE_LOG(LogTemp, Warning, TEXT("Random Potion : Fast Speed"));
}

void ARandomPotionItem::SlowSpeed()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->SetSpeed(250.0f);
	UE_LOG(LogTemp, Warning, TEXT("Random Potion : Slow Speed"));
}

void ARandomPotionItem::ReverseKey()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->ReverseKey();
	UE_LOG(LogTemp, Warning, TEXT("Random Potion : ReverseKey"));
}



