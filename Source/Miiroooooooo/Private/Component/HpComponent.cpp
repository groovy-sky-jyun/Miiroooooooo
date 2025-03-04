// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/HpComponent.h"
#include "BaseTrap.h"
#include "Engine/World.h"
#include "EngineUtils.h"

// Sets default values
AHpComponent::AHpComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void AHpComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//Dalegate : Damaged Trap
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

bool AHpComponent::bIsFullHealth()
{
	if (CurrentHealth >= 100)
	{
		return true;
	}
	return false;
}

void AHpComponent::AddHealth(int32 Value)
{
	CurrentHealth += Value;
	if (CurrentHealth > 100)
	{
		CurrentHealth = 100;
	}
}

void AHpComponent::SubHealth(int32 Value)
{
	CurrentHealth -= Value;
	if (CurrentHealth < 0)
	{
		CurrentHealth = 0;
	}
}
