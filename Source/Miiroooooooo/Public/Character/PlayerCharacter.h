// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ItemInventoryComponent.h"
#include "HealthComponent.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class MIIROOOOOOOO_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


// Input Section
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<class UInputAction> LookAroundAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<class UInputAction> UseItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> PickupItemAction;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void LookAround(const FInputActionValue& Value);



// 캐릭터 물리적 요소
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CurrentPitch;

	UFUNCTION(BlueprintCallable)
	void SetSpeed(float Value);

	UFUNCTION(BlueprintCallable)
	void SetOriginSpeed();

	UFUNCTION(BlueprintCallable)
	void ReverseKey();

	UFUNCTION(BlueprintCallable)
	void ReverseOriginKey();

	UPROPERTY()
	bool bIsReverse;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox;

// Item Section
public:
	UPROPERTY()
	class UItemInventoryComponent* ItemComponent; 

	UPROPERTY()
	class UHealthComponent* HealthComponent;

	UFUNCTION(BlueprintCallable)
	void OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex);

	UFUNCTION()
	void PickUpItem();

	UFUNCTION()
	void UseItemKey();


	// Animation Montage
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ThrowingMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SprayMontage;


// Interaction Montage Section
public:
	UFUNCTION()
	void Throwing();

	UFUNCTION()
	void Spraying();
	

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trace")
	class USceneComponent* WallTrace;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemState")
	bool bIsUsedItem = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemState")
	bool bIsUsedGrenade=false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemState")
	bool bIsUsedSpray=false;

};
