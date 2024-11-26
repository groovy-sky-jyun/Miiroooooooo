// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "BasicItem.h"
#include "ItemInteractionComponent.h"
#include "ItemsComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="input")
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

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	class UCameraComponent* CameraComponent;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox;

	// 아이템 수집
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* PressFAction;

	// 아이템 사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* UseItemAction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInteract")
	class UItemInteractionComponent* ItemInteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInteract")
	class UItemsComponent* ItemsComponent;

	UFUNCTION()
	void PickUpItem();

	UFUNCTION(BlueprintCallable, Category = "ItemInteract")
	void OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "ItemInteract")
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex);

	UFUNCTION()
	void UseItemKey();

	//임시 아이템 구현 로직 (나중에 다른 클래스로 옮기기
	UFUNCTION()
	void UseItem(int32 KeyNum);
};
