// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrap.h"
#include "Pit.generated.h"



UCLASS()
class MIIROOOOOOOO_API APit : public ABaseTrap
{
	GENERATED_BODY()
public:
	virtual void SetDamage() override;
	virtual void OverlapToPlayer() override;
	virtual void DamageThePlayer() override;


};
