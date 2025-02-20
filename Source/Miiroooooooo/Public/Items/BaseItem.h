// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStructure.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseItem.generated.h"

UCLASS()
class MIIROOOOOOOO_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom_Reference")
	UWidgetComponent* InteractionWidget;
	
	UFUNCTION()
	void SetInteractWidget(bool value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EItemName ItemName;

	virtual void SetName() {};

	virtual EItemName GetName() { return ItemName; };
};
