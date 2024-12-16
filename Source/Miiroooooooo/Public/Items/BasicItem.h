// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Engine/DataAsset.h"
#include "BasicItem.generated.h"

UENUM(BlueprintType)
enum class EItem : uint8
{
	Object UMETA(DisplayName = "Object"),
	Liquid UMETA(DisplayName = "Liquid")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	TreasureChest UMETA(DisplayName = "TreasureChest"),
	Wear UMETA(DisplayName = "Wear")
};

USTRUCT(BlueprintType)
struct FItemStructure : public FTableRowBase
{
	GENERATED_BODY()

	// Inventory Ä­ À§Ä¡ ³ªÅ¸³¿, 0ºÎÅÍ ½ÃÀÛ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Explanation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItem ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;
};


UCLASS()
class MIIROOOOOOOO_API ABasicItem : public AActor
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
	class UWidgetComponent* ItemWidgetComponent; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	class UHealthComponent* HealthInstance;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInteract")
	FName RowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInteract")
	EItemType ItemType;

	UFUNCTION(BlueprintCallable)
	FName GetRowName();

	UFUNCTION(BlueprintCallable)
	EItemType GetItemType();

	UFUNCTION(BlueprintCallable)
	void SetInteractWidget(bool value);

public:
	virtual void UseItem();
};