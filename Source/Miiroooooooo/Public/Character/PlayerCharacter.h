// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "HUDWidget.h"
#include "InteractionItemComponent.h"
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

	// 캐릭터 움직임
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	class UInputAction* LookAroundAction;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void LookAround(const FInputActionValue& Value);


	// 캐릭터 물리적 요소
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

	
public:
	// Widget 초기화
	UFUNCTION(BlueprintCallable)
	void SetWidgetToViewPort();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Custom_Reference")
	//UHUDWidget* HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom_Reference")
	TSubclassOf<UHUDWidget> WidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHUDWidget* PlayerWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AInteractionItemComponent* ItemComponent;

	UFUNCTION(BlueprintCallable)
	void OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex);

	// 아이템 수집 --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* PressFAction;

	UFUNCTION()
	void PickUpItem();
	//---



	/*
	// 아이템 사용 --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* UseItemAction;

	UFUNCTION()
	void UseItemKey();
	//---
	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	//class UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	class UInteractionItems* ItemsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UHealthComponent* HealthComponent;
	*/
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trace")
	class USceneComponent* WallTrace;
};
