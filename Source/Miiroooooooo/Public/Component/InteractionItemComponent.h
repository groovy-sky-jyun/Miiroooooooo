// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.h"
#include "InteractionItemComponent.generated.h"

class UHUDWidget;

UCLASS()
class MIIROOOOOOOO_API AInteractionItemComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionItemComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomReference")
	UDataTable* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomReference")
	UHUDWidget* HUDWidgetComponent; 

	UFUNCTION()
	void SetUsableItemFromData();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AddOverlapItem(ABaseItem* Item);

	UFUNCTION()
	void RemoveOverlapItem(ABaseItem* Item);

public:
	UFUNCTION()
	void PickUpAnItem();

	UFUNCTION()
	ABaseItem* GetItemCloseToPlayer();

	UFUNCTION()
	UTexture2D* GetItemTexture(FName ItemName);

	UFUNCTION()
	void AddEquipmentItem(FName ItemName);

	UFUNCTION()
	void AddUsableItem(FName ItemName);

	UFUNCTION()
	FName GetRandomItem();

	UFUNCTION()
	EItemName GetProbabilisticItem();

	UFUNCTION()
	FName EnumValueToFName(EItemName Value);

public:
	//UFUNCTION()
	//void UseItem();

private:
	UPROPERTY()
	TArray<ABaseItem*> OverlapItems;

	UPROPERTY()
	TArray<int32> OverlapNum;

	UPROPERTY()
	int32 UsableItemTotal;

	UPROPERTY()
	TObjectPtr<class APlayerCharacter> Player;

	UPROPERTY(VisibleAnywhere)
	TMap<FName, int32> ItemList;

	UPROPERTY(VisibleAnywhere)
	TMap<EItemName, float> UsableItemProbabilistic;

	UPROPERTY(VisibleAnywhere)
	float ProbabilitySum; //ШЎЗќЧе
};
