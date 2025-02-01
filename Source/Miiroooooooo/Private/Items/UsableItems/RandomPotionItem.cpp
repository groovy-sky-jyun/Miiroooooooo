// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomPotionItem.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

void ARandomPotionItem::UseItem()
{
	int Value = FMath::RandRange(0, 4);
	switch (Value) {
	case 0:
		AddHealth();
		break;
	case 1:
		SubHealth();
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

void ARandomPotionItem::SetName()
{
	ItemName = FName("RandomPotion");
}

FName ARandomPotionItem::GetName()
{
	return ItemName;
}

void ARandomPotionItem::AddHealth()
{
	
}

void ARandomPotionItem::SubHealth()
{
	
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



