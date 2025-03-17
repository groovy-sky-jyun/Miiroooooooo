// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "SprayItem.h"

UABAnimInstance::UABAnimInstance()
{
	MovingTheshould = 3.0f;
	JumpingTheshould = 100.0f;
}

void UABAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<APlayerCharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D(); //XY 크기로 지면의 속력 구함
		bIsIdle = GroundSpeed < MovingTheshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingTheshould);
	}
}

void UABAnimInstance::Throwing(UAnimMontage* Montage)
{
	if (!Montage_IsPlaying(Montage))
	{
		Montage_Play(Montage, 1.0f);
		UE_LOG(LogTemp, Warning, TEXT("Throw Montage Playing"));
	}
}


void UABAnimInstance::Spraying(UAnimMontage* Montage)
{
	if (!Montage_IsPlaying(Montage))
	{
		Montage_Play(Montage, 1.0f);
		UE_LOG(LogTemp, Warning, TEXT("Spray Montage Playing"));
	}
}

void UABAnimInstance::AnimNotify_DrawSpray()
{
	UWorld* World = GetWorld();
	ASprayItem* Spray = World->SpawnActor<ASprayItem>(ASprayItem::StaticClass());
	Spray->DrawSpray();
	Spray->Destroy();
}
