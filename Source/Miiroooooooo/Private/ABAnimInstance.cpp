// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UABAnimInstance::UABAnimInstance()
{
	MovingTheshould = 3.0f;
	JumpingTheshould = 100.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontageThrowRef(TEXT("/Game/GameContent/Animation/AnimationSequence/AM_Throw.AM_Throw"));
	if (AnimMontageThrowRef.Object)
	{
		ThrowingMontage = AnimMontageThrowRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontageSprayRef(TEXT("/Script/Engine.AnimMontage'/Game/GameContent/Animation/AM_Spray.AM_Spray'"));
	if (AnimMontageSprayRef.Object)
	{
		SprayMontage = AnimMontageSprayRef.Object;
	}
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

void UABAnimInstance::Throwing()
{
	
	if (!Montage_IsPlaying(ThrowingMontage))
	{
		Montage_Play(ThrowingMontage, 1.0f);
		UE_LOG(LogTemp, Warning, TEXT("Throw Montage Playing"));
	}
}

void UABAnimInstance::Spraying()
{
	if (!SprayMontage)
	{
		return;
	}
	if (!Montage_IsPlaying(SprayMontage))
	{
		Montage_Play(SprayMontage, 1.0f);
		UE_LOG(LogTemp, Warning, TEXT("Spray Montage Playing"));
	}
}
