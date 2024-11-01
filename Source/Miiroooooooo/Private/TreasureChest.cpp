// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureChest.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"


// Sets default values
ATreasureChest::ATreasureChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	* 보물상자 CollisionBox 설정
	*/
	TreasureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh")); 
	RootComponent = TreasureMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(TreasureMesh);
	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	//충돌감지(물리적x)
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
	CollisionBox->SetGenerateOverlapEvents(true);

	IsOverlap = false;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATreasureChest::OnOverlapStart);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ATreasureChest::OnOverlapEnd);

	PressKeyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	PressKeyWidgetComponent->SetupAttachment(RootComponent);
	PressKeyWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	PressKeyWidgetComponent->SetDrawSize(FVector2D(80.0f, 80.0f));
	PressKeyWidgetComponent->SetVisibility(false); 
}

// Called when the game starts or when spawned
void ATreasureChest::BeginPlay()
{
	Super::BeginPlay();
	
	if (PressKeyWidgetClass)
	{
		PressKeyWidgetComponent->SetWidgetClass(PressKeyWidgetClass);
	}
}

// Called every frame
void ATreasureChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATreasureChest::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	class APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor); 
	if (Player) { 
		PressKeyWidgetComponent->SetVisibility(true);
		IsOverlap = true;
		Player->CurrentTreasureChest = this;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TreasureChest: 플레이어 캐릭터가 아닙니다.")); 
	}
}

void ATreasureChest::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	PressKeyWidgetComponent->SetVisibility(false);
	class APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player) {
		Player->CurrentTreasureChest = nullptr;
	}
	IsOverlap = false;
}



