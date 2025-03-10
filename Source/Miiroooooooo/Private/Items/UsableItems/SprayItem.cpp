// Fill out your copyright notice in the Description page of Project Settings.


#include "SprayItem.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Wall.h"

void ASprayItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Use Item Spray"));
	DrawSpray();
}

bool ASprayItem::bIsAvailableItem()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	check(PlayerPawn);

	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerPawn);
	check(Player);

	StartLocation = Player->GetActorLocation();
	StartLocation.Z += 20.0f;
	EndLocation = StartLocation + Player->GetActorForwardVector() * 300.0f;

	/*
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, Channel);

	//플레이어는 라인 트레이스가 무시하도록 설정
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, Channel, QueryParams);
	*/

	// 충돌 처리 방식
	FCollisionQueryParams CollisionParams = FCollisionQueryParams(FName(TEXT("LineTrace")), true, this);

	bool bIsHit = GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_WorldStatic, //collision channel: 보이는 객체
		CollisionParams
	);

	if (bIsHit)
	{
		AActor* HitActor = HitResult.GetActor();
		AWall* HitWall = Cast<AWall>(HitActor);
		if (HitWall != nullptr)
		{
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}

void ASprayItem::DrawSpray()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	check(PlayerPawn);

	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerPawn);
	check(Player);

	Player->Spraying();

	// Debugging: Line Trace Output to screen
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 2.0f, 0, 1.0f);

	FVector DecalLocation = HitResult.ImpactPoint;
	FRotator DecalRotator = HitResult.ImpactNormal.ToOrientationRotator();
	FVector DecalSize(64.0f, 130.0f, 100.0f);

	FString MaterialPath = TEXT("/Game/GameContent/Item/Assets/Material/M_Spray.M_Spray");
	UMaterialInterface* DecalMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *MaterialPath));
	if (!DecalMaterial) {
		UE_LOG(LogTemp, Warning, TEXT("DecalMaterial is invalid or not set!"));
	}

	UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(),
		DecalMaterial,
		DecalSize,
		DecalLocation,
		DecalRotator,
		0.0f // Life Span: infinity
	);
	if (Decal) {

		UE_LOG(LogTemp, Warning, TEXT("Decal Spawned Successfully!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Spawn Decal!"));
	}
}

