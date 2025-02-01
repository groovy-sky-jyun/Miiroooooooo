// Fill out your copyright notice in the Description page of Project Settings.


#include "UsableItem.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"


// Sets default values
AUsableItem::AUsableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshComponent;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	// 충돌감지(물리적x)
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
	CollisionBox->SetGenerateOverlapEvents(true);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget->SetDrawSize(FVector2D(80.0f, 80.0f));
	InteractionWidget->SetVisibility(false);
}

void AUsableItem::BeginPlay()
{
	Super::BeginPlay();
}

void AUsableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUsableItem::SetInteractWidget(bool value)
{
	InteractionWidget->SetVisibility(value);
}

EItemType AUsableItem::GetItemType()
{
	return ItemType;
}
