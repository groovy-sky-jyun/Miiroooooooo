// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wall.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

// 구조체 선언
USTRUCT(BlueprintType)
struct FStructArray
{
	GENERATED_BODY() 
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AWall*> Row;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<bool> bRow;
};

UENUM(BlueprintType)
enum class EDirectionWall : uint8
{
	Front     UMETA(DisplayName = "Front"),
	Bottom   UMETA(DisplayName = "Bottom"),
	Left   UMETA(DisplayName = "Left"),
	Right  UMETA(DisplayName = "Right")
};

UCLASS()
class MIIROOOOOOOO_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	
	// BP_Wall
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wall")
	TSubclassOf<AWall> BP_Wall;

	// 생성된 Wall 객체 담는 2차 배열
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	TArray<FStructArray> MazeGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	int Width = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	int Height = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	TArray<AWall*> Stack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wall")
	TArray<FStructArray> CheckList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<EDirectionWall, int32> DirectionCountMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int WallCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int FirstRemoveCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PopCount = 0;


	UFUNCTION()
	void GenerateMaze();

	UFUNCTION()
	void MakePassages(int x, int y);

	UFUNCTION()
	TArray<AWall*> CheckVisitList(int x, int y, TArray<AWall*> FourWallList);

	UFUNCTION()
	void DeleteWall(AWall* OriginWall, AWall* NeighborWall); 

	UFUNCTION()
	FString CheckSequenceDirection();

	UFUNCTION()
	void RemoveSequenceList(TArray<AWall*>& List, AWall* Origin);

	UFUNCTION()
	void DirectionCounting(AWall* Origin, AWall* Neighbor);

	UFUNCTION()
	void AddDeleteWall(AWall* Origin);
	
};