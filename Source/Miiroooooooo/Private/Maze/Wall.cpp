
#include "Wall.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

// Sets default values
AWall::AWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WallMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (WallMesh.Succeeded())
	{
		CubeWall = WallMesh.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CubeWall 메쉬를 로드하지 못했습니다."));
	}

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	FrontWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWall"));
	FrontWall->SetupAttachment(RootComponent);
	FrontWall->SetStaticMesh(CubeWall);
	FrontWall->SetRelativeLocation(FVector(WidthSize,0.0f,0.0f));
	FrontWall->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	FrontWall->SetRelativeScale3D(FVector(0.5f, 1.75f, 2.0f));

	FrontCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FrontCollisionBox"));
	FrontCollisionBox->SetupAttachment(FrontWall);

	BottomWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomWall"));
	BottomWall->SetupAttachment(RootComponent);
	BottomWall->SetStaticMesh(CubeWall);
	BottomWall->SetRelativeLocation(FVector(-1 * WidthSize,0.0f,0.0f));
	BottomWall->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	BottomWall->SetRelativeScale3D(FVector(0.5f, 1.75f, 2.0f));

	BottomCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomCollisionBox"));
	BottomCollisionBox->SetupAttachment(BottomWall);

	RightWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWall"));
	RightWall->SetupAttachment(RootComponent);
	RightWall->SetStaticMesh(CubeWall);
	RightWall->SetRelativeLocation(FVector(0.0f, WidthSize, 0.0f));
	RightWall->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	RightWall->SetRelativeScale3D(FVector(0.5f, 1.75f, 2.0f));

	RightCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightCollisionBox"));
	RightCollisionBox->SetupAttachment(RightWall);

	LeftWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWall"));
	LeftWall->SetupAttachment(RootComponent);
	LeftWall->SetStaticMesh(CubeWall);
	LeftWall->SetRelativeLocation(FVector( 0.0f, -1 * WidthSize, 0.0f));
	LeftWall->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	LeftWall->SetRelativeScale3D(FVector(0.5f, 1.75f, 2.0f));

	LeftCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftCollisionBox"));
	LeftCollisionBox->SetupAttachment(LeftWall);

	
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWall::FindCompleteWall()
{
	return IsValid(FrontWall) && IsValid(BottomWall) && IsValid(RightWall) && IsValid(LeftWall);
}

void AWall::DeleteOnceWall(FString WallDirection)
{
	if (WallDirection == "Front" && FrontWall)
	{
		// 상단 벽 삭제
		FrontWall->DestroyComponent();
		FrontWall = nullptr;
		FrontCollisionBox->DestroyComponent();
		FrontCollisionBox = nullptr;
	}
	else if (WallDirection == "Bottom" && BottomWall)
	{
		// 하단 벽 삭제
		BottomWall->DestroyComponent();
		BottomWall = nullptr;
		BottomCollisionBox->DestroyComponent();
		BottomCollisionBox = nullptr;
	}
	else if (WallDirection == "Right" && RightWall)
	{
		// 우측 벽 삭제
		RightWall->DestroyComponent();
		RightWall = nullptr;
		RightCollisionBox->DestroyComponent();
		RightCollisionBox = nullptr;
	}
	else if (WallDirection == "Left" && LeftWall)
	{
		// 좌측 벽 삭제
		LeftWall->DestroyComponent();
		LeftWall = nullptr;
		LeftCollisionBox->DestroyComponent();
		LeftCollisionBox = nullptr;
	}
}

bool AWall::CheckFrontWall()
{
	return IsValid(FrontWall);
}

bool AWall::CheckBottomWall()
{
	return IsValid(BottomWall);
}

bool AWall::CheckRightWall()
{
	return IsValid(RightWall);
}

bool AWall::CheckLeftWall()
{
	return IsValid(LeftWall);
}
