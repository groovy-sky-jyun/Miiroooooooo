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
	
    // ArrWallClass ũ�� �ʱ�ȭ
    MazeGrid.SetNum(Width);
    for (int i = 0; i < MazeGrid.Num(); i++) {
        MazeGrid[i].Row.SetNum(Height);
    }

    // CheckList Class ũ�� �ʱ�ȭ
    CheckList.SetNum(Width);
    for (int i = 0; i < CheckList.Num(); i++) {
        CheckList[i].bRow.SetNum(Height);
    }

    // �̷� �ʱ�ȭ - ����
    GenerateMaze();

    DirectionCountMap.Add(EDirectionWall::Front, 0);
    DirectionCountMap.Add(EDirectionWall::Bottom, 0);
    DirectionCountMap.Add(EDirectionWall::Left, 0);
    DirectionCountMap.Add(EDirectionWall::Right, 0);


    // �游���
    MakePassages(0,0);

    // �Ա�, �ⱸ
    MazeGrid[0].Row[0]->DeleteOnceWall("Bottom"); //�Ա�
    MazeGrid[Width-1].Row[Height-1]->DeleteOnceWall("Front"); //�ⱸ

}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// �̷� �ʱ�ȭ(�� ���� �� �ִ� Wall ���� ����)
void AMazeGenerator::GenerateMaze()
{
    FVector BaseLocation = GetActorLocation();
    FRotator Rotation = GetActorRotation();
    //���� ��ü ������ �̷� ���� (�ʱ�ȭ)
    for (int x = 0; x < Width; x++) {
        for (int y = 0; y < Height; y++) {
            //�� ���� ��ġ ����
            FVector Location = BaseLocation + FVector(x * 400.0f, y * 400.0f, 0.0f);
            //�� ����
            AWall* SpawnWall = GetWorld()->SpawnActor<AWall>(BP_Wall, Location, Rotation);
            if (SpawnWall) {
                //ArrWallClass �� ������ Ŭ���� ����.
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
    * [�湮���� ���� ���̶��]
    * Stack�� Add
    * �湮 = true
    */
    if (!CheckList[x].bRow[y]) { 
        Stack.Add(MazeGrid[x].Row[y]);
        CheckList[x].bRow[y] = true;
    }
    
    /*
    * [�ֺ� �湮���� ���� ť��� List ��������]
    */
    TArray<AWall*> FourWallList;
    FourWallList = CheckVisitList(x, y, FourWallList);

    /*
    * [�ֺ� �湮���� ���� ť�갡 �ϳ��� �ִٸ�]
    * 1) �湮���� ���� ť�� List ����
    * 2) ����ť����� 3�� �̻� ���� �������� �̵��ߴٸ� List���� �ش� ���� ����
    * 3) List ���� ���� ť�� ����
    * 4) ���� ť��� ���� ť�� ������ �� ����
    * 
    * [�ֺ� �湮���� ���� ť�갡 �ϳ��� ���ٸ�]
    * 1) Stack ���� Pop �Ѵ�.
    * 2) Stack �� Top ť�� �ֺ��� �湮���� ���� ť�갡 �ִ��� Ȯ���Ѵ�.
    */
    if (CheckSequenceDirection() != "None") { //���� ���� ���� ���� �ϸ� �ش� ���� ť�� List���� ����
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
    //���� ���� ���� �� Ȯ��
    if (y + 1 < Height) {
        if (FourWallList.Num() < 4 && !CheckList[x].bRow[y+1]) { //�湮���� ���� ���̶��
            FourWallList.Add(MazeGrid[x].Row[y+1]);
        }
    }

    //���� ���� �Ʒ��� �� Ȯ��
    if (y - 1 >= 0) {
        if (FourWallList.Num() < 4 && !CheckList[x].bRow[y-1]) { //�湮���� ���� ���̶��
            FourWallList.Add(MazeGrid[x].Row[y-1]);
        }
    }

    //���� ���� ���� �� Ȯ��
    if (x + 1 < Width) {
        if (FourWallList.Num() < 4 && !CheckList[x+1].bRow[y]) { //�湮���� ���� ���̶��
            FourWallList.Add(MazeGrid[x + 1].Row[y]);
        }
    }

    //���� ���� ���� �� Ȯ��
    if (x - 1 >= 0) {
        if (FourWallList.Num() < 4 && !CheckList[x-1].bRow[y]) { //�湮���� ���� ���̶��
            FourWallList.Add(MazeGrid[x-1].Row[y]);
        }
    }

    return FourWallList;
}

// ť�� ������ ����� �� ����
void AMazeGenerator::DeleteWall(AWall* OriginWall, AWall* NeighborWall) 
{
    int x = OriginWall->IndexX;
    int y = OriginWall->IndexY;
    int nx = NeighborWall->IndexX;
    int ny = NeighborWall->IndexY;

    if (x - nx < 0) { //(0,0)(1,0) ���� ť�� ����
        OriginWall->DeleteOnceWall("Front"); //��
        NeighborWall->DeleteOnceWall("Bottom"); //��
    }
    else if (x - nx > 0) {//(1,0)(0,0) �Ʒ��� ť�� ����
        OriginWall->DeleteOnceWall("Bottom"); //��
        NeighborWall->DeleteOnceWall("Front"); //��
    }
    else if (y - ny < 0) {//(0,0)(0,1) ������ ť�� ����
        OriginWall->DeleteOnceWall("Right"); //��
        NeighborWall->DeleteOnceWall("Left"); //��
    }
    else if (y - ny > 0) {//(0,1)(0,0) ���� ť�� ����
        OriginWall->DeleteOnceWall("Left"); //��
        NeighborWall->DeleteOnceWall("Right"); //��
    }

}

FString AMazeGenerator::CheckSequenceDirection()
{
    /*
    * ���� ť�� ��ġ���� Ȯ������ �� ���������� ������ �̾������� Ȯ��
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
    * ���� ���⿡ ��ġ�ϴ� ť��� List���� ����(List�� �ִٸ�)
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
    * �����ϴ� ���� List�� ���
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
    * List �� �ϳ� ���� ���� �� ����
    */
    if (List.Num() > 0) {
        int32 ShuffleNum = FMath::RandRange(0, List.Num() - 1);
        DeleteWall(MazeGrid[x].Row[y], List[ShuffleNum]);
        UE_LOG(LogTemp, Error, TEXT("Add Delete Wall : List Shuffle[%d][%d]"), List[ShuffleNum]->IndexX, List[ShuffleNum]->IndexY);
    }
   
     
}


