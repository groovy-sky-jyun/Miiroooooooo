// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/HpComponent.h"
#include "BaseTrap.h"
#include "Engine/World.h"
#include "EngineUtils.h"

// Sets default values
AHpComponent::AHpComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void AHpComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<ABaseTrap> It(GetWorld()); It; ++It)
	{
		It->DamagedOnChange.AddUObject(this, &AHpComponent::SubHealth);
	}

}

// Called every frame
void AHpComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHpComponent::AddHealth(float Value)
{
	float NewValue = Value / MaxHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth + NewValue, 0.0f, 1.0f);
}

void AHpComponent::SubHealth(int32 Value)
{
	CurrentHealth -= Value;
}
