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
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABasicItem::OnOverlapStart);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABasicItem::OnOverlapEnd);

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

void ABasicItem::SetRowName(FName NewName)
{
	RowName = NewName;
}

EItemType ABasicItem::GetItemType()
{
	return ItemType;
}

// Overlap 되었을 때 InteractionKeyWidget Visible 실행
void ABasicItem::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APlayerCharacter>()) {
		ItemWidgetComponent->SetVisibility(true);
	}
	
}

// Overlap 끝났을 때 InteractionKeyWidget InVisible실행
void ABasicItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex)
{
	ItemWidgetComponent->SetVisibility(false);
}



void ABasicItem::UseItem()
{
}
