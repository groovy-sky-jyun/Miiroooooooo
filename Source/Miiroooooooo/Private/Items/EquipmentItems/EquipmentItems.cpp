// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentItems.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AEquipmentItems::AEquipmentItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshComponent;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget->SetDrawSize(FVector2D(80.0f, 80.0f));
	InteractionWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void AEquipmentItems::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquipmentItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquipmentItems::SetInteractWidget(bool value)
{
	InteractionWidget->SetVisibility(value);
}

EItemType AEquipmentItems::GetItemType()
{
	return ItemType;
}


