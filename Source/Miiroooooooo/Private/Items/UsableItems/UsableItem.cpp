// Fill out your copyright notice in the Description page of Project Settings.


#include "UsableItem.h"

// Sets default values
AUsableItem::AUsableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

void AUsableItem::BeginPlay()
{
	Super::BeginPlay();
}

void AUsableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
