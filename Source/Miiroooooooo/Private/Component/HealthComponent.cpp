// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/HealthComponent.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHealth = 100;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	/*
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter) {
		if (PlayerCharacter->PlayerWidget)
			ItemWidget = PlayerCharacter->PlayerWidget;
	}*/
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::AddHealth(float Value)
{
	float NewValue = Value / MaxHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth + NewValue, 0.0f,1.0f);
	ItemWidget->UpdateHealth(CurrentHealth);
}

void UHealthComponent::SubHealth(float Value)
{
	float NewValue = Value / MaxHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth - NewValue, 0.0f, 1.0f);
	ItemWidget->UpdateHealth(CurrentHealth);
}

