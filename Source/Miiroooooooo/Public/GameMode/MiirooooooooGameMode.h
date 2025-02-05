// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiirooooooooGameMode.generated.h"

UCLASS(minimalapi)
class AMiirooooooooGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMiirooooooooGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};



