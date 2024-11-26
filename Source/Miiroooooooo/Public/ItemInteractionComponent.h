// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemStructure.h"
#include "MiiroooPlayerController.h"
#include "ItemInteractionComponent.generated.h"

class ABasicItem;
class UItemsComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MIIROOOOOOOO_API UItemInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInteract")
	UDataTable* ItemTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AActor*> OverlapItemList;

	UFUNCTION(BlueprintCallable)
	void AddOverlapItem(AActor* ItemClass);

	UFUNCTION(BlueprintCallable)
	void RemoveOverlapItem(AActor* ItemClass);

	UFUNCTION(BlueprintCallable)
	void AddItemToPlayer();

	UFUNCTION(BlueprintCallable)
	AActor* CloseToPlayer();

	UFUNCTION(BlueprintCallable)
	FItemStructure GetItemStructure(AActor* ItemClass);

	UFUNCTION(BlueprintCallable)
	FItemStructure GetWearStructure(ABasicItem* WearItem);

	UFUNCTION(BlueprintCallable)
	FItemStructure GetLiquidStructure();

	UFUNCTION(BlueprintCallable)
	TArray<FItemStructure> GetStructureForType(EItem ItemType);

	UFUNCTION(BlueprintCallable)
	FItemStructure GetRandomStructure(TArray<FItemStructure> ItemStructures);

	UFUNCTION(BlueprintCallable)
	void CountUpdate(int32 Number);

private:
	UItemsComponent* ItemsComponent;
};
