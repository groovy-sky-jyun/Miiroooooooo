// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/HealthComponent.h"
#include "BaseTrap.h"
#include "Engine/World.h"
#include "EngineUtils.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	CurrentHealth = MaxHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//Dalegate : Damaged Trap
	for (TActorIterator<ABaseTrap> It(GetWorld()); It; ++It)
	{
		It->DamagedOnChange.AddUObject(this, &UHealthComponent::SubHealth);
	}
	
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UHealthComponent::bIsFullHealth()
{
	UE_LOG(LogTemp, Warning, TEXT("CurrentHealth is %d"), CurrentHealth);
	if (CurrentHealth >= 100)
	{
		return true;
	}
	return false;
}

void UHealthComponent::AddHealth(int32 Value)
{
	CurrentHealth += Value;
	if (CurrentHealth > 100)
	{
		CurrentHealth = 100;
	}
}

void UHealthComponent::SubHealth(int32 Value)
{
	CurrentHealth -= Value;
	if (CurrentHealth < 0)
	{
		CurrentHealth = 0;
	}
}
