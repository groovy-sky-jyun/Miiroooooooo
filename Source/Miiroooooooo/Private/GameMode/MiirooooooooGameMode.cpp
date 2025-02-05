// Copyright Epic Games, Inc. All Rights Reserved.

#include "MiirooooooooGameMode.h"
#include "MiirooooooooCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MiirooooGameInstance.h"

AMiirooooooooGameMode::AMiirooooooooGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMiirooooooooGameMode::BeginPlay()
{
	Super::BeginPlay();

	UMiirooooGameInstance* GameInstance = Cast<UMiirooooGameInstance>(GetGameInstance());

}
