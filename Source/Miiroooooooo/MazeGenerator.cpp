// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include "Wall.h"
#include "GameFramework/Actor.h"


// Sets default values
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
	
    // ArrWallClass 크기 초기화
    MazeGrid.SetNum(Width);
    for (int i = 0; i < MazeGrid.Num(); i++) {
        MazeGrid[i].Row.SetNum(Height);
    }

    // CheckList Class 크기 초기화
    CheckList.SetNum(Width);
    for (int i = 0; i < CheckList.Num(); i++) {
        CheckList[i].bRow.SetNum(Height);
    }

    // 미로 초기화 - 생성
    GenerateMaze();

    // 길만들기
    MakePassages(0,0);

    // 입구, 출구
    MazeGrid[0].Row[0]->DeleteOnceWall("Bottom"); //입구
    MazeGrid[Width-1].Row[Height-1]->DeleteOnceWall("Front"); //출구

}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 미로 초기화(네 면이 다 있는 Wall 격자 생성)
void AMazeGenerator::GenerateMaze()
{
    FVector BaseLocation = GetActorLocation();
    FRotator Rotation = GetActorRotation();
    //벽이 전체 온전한 미로 생성 (초기화)
    for (int x = 0; x < Width; x++) {
        for (int y = 0; y < Height; y++) {
            //벽 스폰 위치 설정
            FVector Location = BaseLocation + FVector(x * 160.0f, y * 160.0f, 0.0f);
            //벽 스폰
            AWall* SpawnWall = GetWorld()->SpawnActor<AWall>(BP_Wall, Location, Rotation);
            if (SpawnWall) {
                //ArrWallClass 에 생성된 클래스 담음.
                SpawnWall->IndexX = x;
                SpawnWall->IndexY = y;
                MazeGrid[x].Row[y] = SpawnWall; 
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("Failed to spawn AWall Actor"));
            }
        }
    }
}

void AMazeGenerator::MakePassages(int x, int y)
{
    if (!CheckList[x].bRow[y]) { //방문하지 않은 곳이라면
        Stack.Add(MazeGrid[x].Row[y]);
        CheckList[x].bRow[y] = true;
        UE_LOG(LogTemp, Warning, TEXT("Push [%d][%d]"), x, y);
    }
    
    TArray<AWall*> FourWallList;
    FourWallList = CheckVisitList(x, y, FourWallList); //인접하면서 방문하지 않은 큐브들 모음

    if (FourWallList.Num() > 0) {//인접한 큐브중 방문하지 않은 큐브가 있다면
        // 큐브 랜덤 인덱스 뽑기
        int32 ShuffleNum = FMath::RandRange(0, FourWallList.Num() - 1);

        // 랜덤 큐브와 현재 큐브 사이의 벽 제거
        DeleteWall(MazeGrid[x].Row[y], FourWallList[ShuffleNum]);
        //UE_LOG(LogTemp, Warning, TEXT("Origin [%d][%d], Neighbor [%d][%d]"), x, y, FourWallList[ShuffleNum]->IndexX, FourWallList[ShuffleNum]->IndexY);
        MakePassages(FourWallList[ShuffleNum]->IndexX, FourWallList[ShuffleNum]->IndexY);
    }
    else {//인접한 큐브중 방문하지 않은 큐브가 없다면
        Stack.Pop();
        UE_LOG(LogTemp, Warning, TEXT("Pop [%d][%d]"), x, y);
        UE_LOG(LogTemp, Warning, TEXT("Top [%d][%d]"), Stack.Top()->IndexX, Stack.Top()->IndexY);
        if (Stack.Top()->IndexX != 0 || Stack.Top()->IndexY != 0) {
            MakePassages(Stack.Top()->IndexX, Stack.Top()->IndexY);
        }
    }
}

TArray<AWall*> AMazeGenerator::CheckVisitList(int x, int y, TArray<AWall*> FourWallList)
{
    //현재 블럭의 위측 블럭 확인
    if (y + 1 < Height) {
        if (FourWallList.Num() < 4 && !CheckList[x].bRow[y+1]) { //방문하지 않은 곳이라면
            FourWallList.Add(MazeGrid[x].Row[y+1]);
        }
    }

    //현재 블럭의 아래측 블럭 확인
    if (y - 1 >= 0) {
        if (FourWallList.Num() < 4 && !CheckList[x].bRow[y-1]) { //방문하지 않은 곳이라면
            FourWallList.Add(MazeGrid[x].Row[y-1]);
        }
    }

    //현재 블럭의 우측 블럭 확인
    if (x + 1 < Width) {
        if (FourWallList.Num() < 4 && !CheckList[x+1].bRow[y]) { //방문하지 않은 곳이라면
            FourWallList.Add(MazeGrid[x + 1].Row[y]);
        }
    }

    //현재 블럭의 좌측 블럭 확인
    if (x - 1 >= 0) {
        if (FourWallList.Num() < 4 && !CheckList[x-1].bRow[y]) { //방문하지 않은 곳이라면
            FourWallList.Add(MazeGrid[x-1].Row[y]);
        }
    }

    return FourWallList;
}

// 큐브 사이의 공통된 벽 제거
void AMazeGenerator::DeleteWall(AWall* OriginWall, AWall* NeighborWall) 
{
    int x = OriginWall->IndexX;
    int y = OriginWall->IndexY;
    int nx = NeighborWall->IndexX;
    int ny = NeighborWall->IndexY;

    if (x - nx < 0) { //(0,0)(1,0) 위쪽 큐브 선택
        OriginWall->DeleteOnceWall("Front"); //상
        NeighborWall->DeleteOnceWall("Bottom"); //하
    }
    else if (x - nx > 0) {//(1,0)(0,0) 아래쪽 큐브 선택
        OriginWall->DeleteOnceWall("Bottom"); //하
        NeighborWall->DeleteOnceWall("Front"); //상
    }
    else if (y - ny < 0) {//(0,0)(0,1) 오른쪽 큐브 선택
        OriginWall->DeleteOnceWall("Right"); //우
        NeighborWall->DeleteOnceWall("Left"); //좌
    }
    else if (y - ny > 0) {//(0,1)(0,0) 왼쪽 큐브 선택
        OriginWall->DeleteOnceWall("Left"); //좌
        NeighborWall->DeleteOnceWall("Right"); //우
    }
}
