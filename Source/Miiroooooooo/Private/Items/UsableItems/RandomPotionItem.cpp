// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomPotionItem.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "MiiroooPlayerController.h"

bool ARandomPotionItem::bIsAvailableItem()
{
	return true;
}

void ARandomPotionItem::UseItem()
{
	int Value = FMath::RandRange(0, 4);
	switch (Value) {
	case 0:
		AddHealth();
		break;
	case 1:
		DamageHealth();
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

void ARandomPotionItem::AddHealth()
{
	AMiiroooPlayerController* PlayerController = Cast<AMiiroooPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->AddHealth(HealValue);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UHealthComponent* HealthComponent = PlayerCharacter->HealthComponent;
	HealthComponent->AddHealth(HealValue);
}

void ARandomPotionItem::DamageHealth()
{
	AMiiroooPlayerController* PlayerController = Cast<AMiiroooPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->DamageHealth(DamageValue);
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UHealthComponent* HealthComponent = PlayerCharacter->HealthComponent;
	HealthComponent->SubHealth(DamageValue);
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



