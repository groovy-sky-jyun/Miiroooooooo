// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicItem.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"


// Sets default values
ABasicItem::ABasicItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static Mesh
	SM_Treasure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = SM_Treasure;

	// 보물상자 CollisionBox 설정
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(SM_Treasure);
	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	// 충돌감지(물리적x)
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
	CollisionBox->SetGenerateOverlapEvents(true);

	// Widget Interaction
	ItemWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	ItemWidgetComponent->SetupAttachment(RootComponent);
	ItemWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	ItemWidgetComponent->SetDrawSize(FVector2D(80.0f, 80.0f));
	ItemWidgetComponent->SetVisibility(false); 
}

void ABasicItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABasicItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FName ABasicItem::GetRowName()
{
	return RowName;
}

EItemType ABasicItem::GetItemType()
{
	return ItemType;
}

void ABasicItem::SetInteractWidget(bool value)
{
	ItemWidgetComponent->SetVisibility(value);
}

void ABasicItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("BasicItem : UseItem() : Check ItemClass"));
}

void ABasicItem::SetRowName()
{
	UE_LOG(LogTemp, Warning, TEXT("BasicItem : SetRowName() : Check ItemClass"));
}
