// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "EquipmentItems.generated.h"

UCLASS()
class MIIROOOOOOOO_API AEquipmentItems : public ABaseItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipmentItems();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void EffectOnProssession() {};

	virtual EItemType GetItemType() override { return EItemType::Equipment; };

	virtual void SetName() override {};
};
