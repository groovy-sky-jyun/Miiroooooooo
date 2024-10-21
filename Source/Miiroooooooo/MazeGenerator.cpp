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

    DirectionCountMap.Add(EDirectionWall::Front, 0);
    DirectionCountMap.Add(EDirectionWall::Bottom, 0);
    DirectionCountMap.Add(EDirectionWall::Left, 0);
    DirectionCountMap.Add(EDirectionWall::Right, 0);

    PreviousWall = MazeGrid[0].Row[0];
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
            FVector Location = BaseLocation + FVector(x * 400.0f, y * 400.0f, 0.0f);
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
    /*
    * [방문하지 않은 곳이라면]
    * Stack에 Add
    * 방문 = true
    */
    if (!CheckList[x].bRow[y]) { 
        Stack.Add(MazeGrid[x].Row[y]);
        CheckList[x].bRow[y] = true;
    }
    
    /*
    * [주변 방문하지 않은 큐브들 List 가져오기]
    */
    TArray<AWall*> FourWallList;
    FourWallList = CheckVisitList(x, y, FourWallList); 
   
    /*
    * [주변 방문하지 않은 큐브가 하나라도 있다면]
    * 1) List 에서 랜덤으로 한개 큐브 뽑음
    * 2) 랜덤 큐브와 현재 큐브 사이의 벽 제거
    * 3) 4개 이상 연속되어있는 벽이 있다면 랜덤 한개 뚫음
    * 
    * [주변 방문하지 않은 큐브가 하나라도 없다면]
    * 1) Stack 에서 Pop 한다.
    * 2) Stack 의 Top 큐브 주변에 방문하지 않은 큐브가 있는지 확인한다.
    */
    if (FourWallList.Num() > 0) {

        int32 ShuffleNum = FMath::RandRange(0, FourWallList.Num() - 1);
        DeleteWall(MazeGrid[x].Row[y], FourWallList[ShuffleNum]);
        WallDirectionCount(MazeGrid[x].Row[y]);
        PreviousWall = MazeGrid[x].Row[y];
        MakePassages(FourWallList[ShuffleNum]->IndexX, FourWallList[ShuffleNum]->IndexY);
    }
    else {
        AWall* PopCube = Stack.Pop();
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

void AMazeGenerator::WallDirectionCount(AWall* OriginWall)
{
    int x = OriginWall->IndexX;
    int y = OriginWall->IndexY;

    /* 
    * [origin 큐브의 상하좌우면 중 어떤 면이 남아있는지를 확인]
    * x가 0이면 BottomWall은 포함하지 않는다.
    * y가 0이면 LeftWall은 포함하지 않는다.
    * x가 height-1 이면 FrontWall 은 포함하지 않는다.
    * y가 width-1 이면 RightWall 은 포함하지 않는다.
    * 벽이 끊기면 해당 벽은 카운트를 초기화시킨다.
    */ 
    if (OriginWall->CheckFrontWall() && x != Height - 1) {
        DirectionCountMap[EDirectionWall::Front]++;
        UE_LOG(LogTemp, Error, TEXT("4Wall add MazeGrid[%d][%d] : Front %d"), x, y, DirectionCountMap[EDirectionWall::Front]);
    }
    else if (!OriginWall->CheckFrontWall()) {
        DirectionCountMap[EDirectionWall::Front]=0;
    }

    if (OriginWall->CheckBottomWall() && x != 0) {
        DirectionCountMap[EDirectionWall::Bottom]++;
        UE_LOG(LogTemp, Error, TEXT("4Wall add MazeGrid[%d][%d] : Bottom %d"), x, y, DirectionCountMap[EDirectionWall::Bottom]);
    }
    else if (!OriginWall->CheckBottomWall()) {
        DirectionCountMap[EDirectionWall::Bottom] = 0;
    }

    if (OriginWall->CheckRightWall() && y != Width -1) {
        DirectionCountMap[EDirectionWall::Right]++;
        UE_LOG(LogTemp, Error, TEXT("4Wall add MazeGrid[%d][%d] : Right %d"), x, y, DirectionCountMap[EDirectionWall::Right]);
    }
    else if (!OriginWall->CheckRightWall()) {
        DirectionCountMap[EDirectionWall::Right] = 0;
    }

    if (OriginWall->CheckLeftWall() && y != 0) {
        DirectionCountMap[EDirectionWall::Left]++;
        UE_LOG(LogTemp, Error, TEXT("4Wall add MazeGrid[%d][%d] : Left %d"), x, y, DirectionCountMap[EDirectionWall::Left]);
    }
    else if (!OriginWall->CheckLeftWall()) {
        DirectionCountMap[EDirectionWall::Left] = 0;
    }


    /*
   * [연속으로 4개의 벽이 이어져 있는곳 확인]
   * if(Front 가 연속으로 이어져 있다면)
   *    OriginWall 와 위의 큐브 사이 벽 허문다.
   * if(Bottom 가 연속으로 이어져 있다면)
   *    OriginWall 와 아래 큐브 사이 벽 허문다.
   * if(Right 가 연속으로 이어져 있다면)
   *    OriginWall 와 오른쪽 큐브 사이 벽 허문다.
   * if(Left 가 연속으로 이어져 있다면)
   *    OriginWall 와 왼쪽 큐브 사이 벽 허문다.
   */
    /*
    * 지금 코드는 무조건 밑에서 위로, 왼쪽에서 오른쪽으로 이어지는 길을 대표적으로 생각했다.
    * 하지만 위에서 아래로, 오른쪽에서 왼쪽으로 이어지는 길에 대해서는 shufflenum만큼 빼주는게 아니라
    * 더해주어야한다. 이러한 경우도 추가해야한다.
    */
    int32 ShuffleNum = FMath::RandRange(0, 3);
    if (DirectionCountMap[EDirectionWall::Front] >= 4) {
        if(y < PreviousWall->IndexY) {//왼쪽으로 가는 방향
            if (x + 1 < Height && y + ShuffleNum < Width) {
                MazeGrid[x].Row[y + ShuffleNum]->DeleteOnceWall("Front");
                MazeGrid[x + 1].Row[y + ShuffleNum]->DeleteOnceWall("Bottom");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Front"), x, y + ShuffleNum);
            }
        }
        else { //오른쪽으로 가는 방향
            if (x + 1 < Height && y - ShuffleNum >= 0) {
                MazeGrid[x].Row[y - ShuffleNum]->DeleteOnceWall("Front");
                MazeGrid[x + 1].Row[y - ShuffleNum]->DeleteOnceWall("Bottom");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Front"), x, y - ShuffleNum);
            }
        }
        DirectionCountMap[EDirectionWall::Front] = 0;
    }
    else if (DirectionCountMap[EDirectionWall::Bottom] >= 4) {
        if (y < PreviousWall->IndexY) {//왼쪽으로 가는 방향
            if (x - 1 >= 0 && y + ShuffleNum < Width) {
                MazeGrid[x].Row[y + ShuffleNum]->DeleteOnceWall("Bottom");
                MazeGrid[x - 1].Row[y + ShuffleNum]->DeleteOnceWall("Front");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Bottom"), x, y + ShuffleNum);
            }
        }
        else {//오른쪽으로 가는 방향
            if (x - 1 >= 0 && y - ShuffleNum >= 0) { 
                MazeGrid[x].Row[y - ShuffleNum]->DeleteOnceWall("Bottom"); 
                MazeGrid[x - 1].Row[y - ShuffleNum]->DeleteOnceWall("Front"); 
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Bottom"), x, y - ShuffleNum); 
            }
        }
        DirectionCountMap[EDirectionWall::Bottom] = 0;
    }
    else if (DirectionCountMap[EDirectionWall::Right] >= 4) {
        if (x < PreviousWall->IndexX) {//아래쪽으로 가는 방향
            if (y + 1 < Width && x + ShuffleNum < Height) {
                MazeGrid[x + ShuffleNum].Row[y]->DeleteOnceWall("Right");
                MazeGrid[x + ShuffleNum].Row[y + 1]->DeleteOnceWall("Left");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Right"), x + ShuffleNum, y);
            }
        }
        else {//위쪽으로 가는 방향
            if (y + 1 < Width && x - ShuffleNum >= 0) {
                MazeGrid[x - ShuffleNum].Row[y]->DeleteOnceWall("Right");
                MazeGrid[x - ShuffleNum].Row[y + 1]->DeleteOnceWall("Left");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Right"), x - ShuffleNum, y);
            }
        }
        DirectionCountMap[EDirectionWall::Right] = 0;
    }
    else if (DirectionCountMap[EDirectionWall::Left] >= 4) {
        if (x < PreviousWall->IndexX) {//아래쪽으로 가는 방향
            if (y - 1 >= 0 && x + ShuffleNum <Height) {
                MazeGrid[x + ShuffleNum].Row[y]->DeleteOnceWall("Left");
                MazeGrid[x + ShuffleNum].Row[y - 1]->DeleteOnceWall("Right");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Left"), x + ShuffleNum, y);
            }
        }
        else {
            if (y - 1 >= 0 && x - ShuffleNum >= 0) {
                MazeGrid[x - ShuffleNum].Row[y]->DeleteOnceWall("Left");
                MazeGrid[x - ShuffleNum].Row[y - 1]->DeleteOnceWall("Right");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Left"), x - ShuffleNum, y);
            }
        }
        DirectionCountMap[EDirectionWall::Left] = 0;
    }
    
}
