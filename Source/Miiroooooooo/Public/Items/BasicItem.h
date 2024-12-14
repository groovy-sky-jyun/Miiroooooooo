// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "ItemInterface.h"
#include "BasicItem.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	TreasureChest UMETA(DisplayName="TreasureChest"),
	Wear UMETA(DisplayName="Wear")
};

UCLASS()
class MIIROOOOOOOO_API ABasicItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UStaticMeshComponent* SM_Treasure;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UWidgetComponent* ItemWidgetComponent; 

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInteract")
	FName RowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInteract")
	EItemType ItemType;

	UFUNCTION(BlueprintCallable, Category = "ItemInteract")
	void OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "ItemInteract")
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex);

public:
	virtual void UseItem() override;
	virtual FName GetRowName() override;
};