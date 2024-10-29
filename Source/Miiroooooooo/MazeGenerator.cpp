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
    UE_LOG(LogTemp, Log, TEXT("MazeGrid : [%d][%d]"), x, y);
    FirstRemoveCount++;
    WallCount++;
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
    * 1) 방문하지 않은 큐브 List 생성
    * 2) 현재큐브까지 3개 이상 같은 방향으로 이동했다면 List에서 해당 방향 제외
    * 3) List 에서 랜덤 큐브 뽑음
    * 4) 랜덤 큐브와 현재 큐브 사이의 벽 제거
    * 
    * [주변 방문하지 않은 큐브가 하나라도 없다면]
    * 1) Stack 에서 Pop 한다.
    * 2) Stack 의 Top 큐브 주변에 방문하지 않은 큐브가 있는지 확인한다.
    */
    if (CheckSequenceDirection() != "None") { //방향 연속 조건 위배 하면 해당 방향 큐브 List에서 제거
        RemoveSequenceList(FourWallList, MazeGrid[x].Row[y]);
    }
    
    for (int i = 0; i < FourWallList.Num(); i++) {
        UE_LOG(LogTemp, Warning, TEXT("FourWallList[%d][%d]"), FourWallList[i]->IndexX, FourWallList[i]->IndexY);
    }

    if (FourWallList.Num() > 0) {
        int32 ShuffleNum = FMath::RandRange(0, FourWallList.Num() - 1);
        DeleteWall(MazeGrid[x].Row[y], FourWallList[ShuffleNum]);
        DirectionCounting(MazeGrid[x].Row[y], FourWallList[ShuffleNum]);
        if (FirstRemoveCount == 4 || WallCount == 15) {
            AddDeleteWall(MazeGrid[x].Row[y]);
            WallCount = 0;
        }
        MakePassages(FourWallList[ShuffleNum]->IndexX, FourWallList[ShuffleNum]->IndexY);
    }
    else {
        Stack.Pop();
        PopCount++;
        if (PopCount == 10) {
            AddDeleteWall(MazeGrid[x].Row[y]);
            PopCount = 0;
        }
        if (Stack.Top()->IndexX != 0 || Stack.Top()->IndexY != 0) {
            MakePassages(Stack.Top()->IndexX, Stack.Top()->IndexY);
        }
        else {
            return;
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

FString AMazeGenerator::CheckSequenceDirection()
{
    /*
    * 현재 큐브 위치에서 확인했을 때 연속적으로 방향이 이어졌는지 확인
    */
    if (DirectionCountMap[EDirectionWall::Front] >= 2) {
        return "Front";
    }
    else if (DirectionCountMap[EDirectionWall::Bottom] >= 2) {
        return "Bottom";
    }
    else if (DirectionCountMap[EDirectionWall::Right] >= 2) {
        return "Right";
    }
    else if (DirectionCountMap[EDirectionWall::Left] >= 2) {
        return "Left";
    }
    else 
        return "None";
}

void AMazeGenerator::RemoveSequenceList(TArray<AWall*>& List, AWall* Origin)
{   /*
    * 연속 방향에 위치하는 큐브는 List에서 제거(List에 있다면)
    */
    int x = Origin->IndexX;
    int y = Origin->IndexY;
    FString Direction = CheckSequenceDirection();

    if (Direction == "Front" && x+1<Height) {
        if(List.Contains(MazeGrid[x + 1].Row[y]))
            List.Remove(MazeGrid[x + 1].Row[y]);
    }
    else if(Direction == "Bottom" && x-1>=0) {
        if(List.Contains(MazeGrid[x - 1].Row[y]))
            List.Remove(MazeGrid[x - 1].Row[y]);
    }
    else if (Direction == "Right" && y+1<Width) {
        if(List.Contains(MazeGrid[x].Row[y + 1]))
            List.Remove(MazeGrid[x].Row[y+1]);
    }
    else if (Direction == "Left" && y-1>=0) {
        if(List.Contains(MazeGrid[x].Row[y - 1]))
            List.Remove(MazeGrid[x].Row[y-1]);
    }
}

void AMazeGenerator::DirectionCounting(AWall* Origin, AWall* Neighbor)
{
    int x = Origin->IndexX;
    int y = Origin->IndexY;
    int nx = Neighbor->IndexX;
    int ny = Neighbor->IndexY;

    if (x - nx < 0) {
        DirectionCountMap[EDirectionWall::Front]++;
        DirectionCountMap[EDirectionWall::Bottom] = 0;
        DirectionCountMap[EDirectionWall::Right] = 0;
        DirectionCountMap[EDirectionWall::Left] = 0;
    }
    else if (x - nx > 0) {
        DirectionCountMap[EDirectionWall::Front]=0;
        DirectionCountMap[EDirectionWall::Bottom]++;
        DirectionCountMap[EDirectionWall::Right] = 0;
        DirectionCountMap[EDirectionWall::Left] = 0;
    }
    else if (y - ny < 0) {
        DirectionCountMap[EDirectionWall::Front] = 0;
        DirectionCountMap[EDirectionWall::Bottom] = 0;
        DirectionCountMap[EDirectionWall::Right]++;
        DirectionCountMap[EDirectionWall::Left] = 0;
    }
    else if (y - ny > 0) {
        DirectionCountMap[EDirectionWall::Front] = 0;
        DirectionCountMap[EDirectionWall::Bottom] = 0;
        DirectionCountMap[EDirectionWall::Right] = 0;
        DirectionCountMap[EDirectionWall::Left]++;
    }
        
}

void AMazeGenerator::AddDeleteWall(AWall* Origin)
{
    /*
    * 존재하는 벽만 List에 담기
    */
    TArray<AWall*> List;
    int x = Origin->IndexX;
    int y = Origin->IndexY;

    if (x + 1 < Height && Origin->CheckFrontWall()) {
        List.Add(MazeGrid[x + 1].Row[y]);
    }
    if (x - 1 >= 0 && Origin->CheckBottomWall()) {
        List.Add(MazeGrid[x - 1].Row[y]);
    }
    if (y + 1 < Width && Origin->CheckRightWall()) {
        List.Add(MazeGrid[x].Row[y + 1]);
    }
    if (y - 1 >= 0 && Origin->CheckLeftWall()) {
        List.Add(MazeGrid[x].Row[y - 1]);
    }

    /*
    * List 중 하나 랜덤 선택 후 삭제
    */
    if (List.Num() > 0) {
        int32 ShuffleNum = FMath::RandRange(0, List.Num() - 1);
        DeleteWall(MazeGrid[x].Row[y], List[ShuffleNum]);
        UE_LOG(LogTemp, Error, TEXT("Add Delete Wall : List Shuffle[%d][%d]"), List[ShuffleNum]->IndexX, List[ShuffleNum]->IndexY);
    }
   
     
}


