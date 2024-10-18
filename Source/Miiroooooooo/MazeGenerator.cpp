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
            FVector Location = BaseLocation + FVector(x * 160.0f, y * 160.0f, 0.0f);
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
    if (!CheckList[x].bRow[y]) { //�湮���� ���� ���̶��
        Stack.Add(MazeGrid[x].Row[y]);
        CheckList[x].bRow[y] = true;
        UE_LOG(LogTemp, Warning, TEXT("Push [%d][%d]"), x, y);
    }
    
    TArray<AWall*> FourWallList;
    FourWallList = CheckVisitList(x, y, FourWallList); //�����ϸ鼭 �湮���� ���� ť��� ����

    if (FourWallList.Num() > 0) {//������ ť���� �湮���� ���� ť�갡 �ִٸ�
        // ť�� ���� �ε��� �̱�
        int32 ShuffleNum = FMath::RandRange(0, FourWallList.Num() - 1);

        // ���� ť��� ���� ť�� ������ �� ����
        DeleteWall(MazeGrid[x].Row[y], FourWallList[ShuffleNum]);
        //UE_LOG(LogTemp, Warning, TEXT("Origin [%d][%d], Neighbor [%d][%d]"), x, y, FourWallList[ShuffleNum]->IndexX, FourWallList[ShuffleNum]->IndexY);
        MakePassages(FourWallList[ShuffleNum]->IndexX, FourWallList[ShuffleNum]->IndexY);
    }
    else {//������ ť���� �湮���� ���� ť�갡 ���ٸ�
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
