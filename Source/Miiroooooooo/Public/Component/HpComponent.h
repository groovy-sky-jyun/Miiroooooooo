// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HpComponent.generated.h"

UCLASS()
class MIIROOOOOOOO_API AHpComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHpComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	bool bIsFullHealth();

	UFUNCTION(BlueprintCallable)
	void AddHealth(int32 Value);

	UFUNCTION(BlueprintCallable)
	void SubHealth(int32 Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth = 100;

private:
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;
};

