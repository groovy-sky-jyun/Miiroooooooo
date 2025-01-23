// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UCLASS()
class MIIROOOOOOOO_API AWall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	UStaticMesh* CubeWall;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* FrontCollisionBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* BottomCollisionBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* RightCollisionBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* LeftCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	UStaticMeshComponent* FrontWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	UStaticMeshComponent* BottomWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	UStaticMeshComponent* RightWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	UStaticMeshComponent* LeftWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	float WidthSize = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	int IndexX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	int IndexY;


	UFUNCTION()
	bool FindCompleteWall();

	UFUNCTION()
	void DeleteOnceWall(FString WallDirection);
	
	UFUNCTION()
	bool CheckFrontWall();
	UFUNCTION()
	bool CheckBottomWall();
	UFUNCTION()
	bool CheckRightWall();
	UFUNCTION()
	bool CheckLeftWall();
};
