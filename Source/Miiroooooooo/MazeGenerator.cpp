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

    PreviousWall = MazeGrid[0].Row[0];
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
    * 1) List ���� �������� �Ѱ� ť�� ����
    * 2) ���� ť��� ���� ť�� ������ �� ����
    * 3) 4�� �̻� ���ӵǾ��ִ� ���� �ִٸ� ���� �Ѱ� ����
    * 
    * [�ֺ� �湮���� ���� ť�갡 �ϳ��� ���ٸ�]
    * 1) Stack ���� Pop �Ѵ�.
    * 2) Stack �� Top ť�� �ֺ��� �湮���� ���� ť�갡 �ִ��� Ȯ���Ѵ�.
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

void AMazeGenerator::WallDirectionCount(AWall* OriginWall)
{
    int x = OriginWall->IndexX;
    int y = OriginWall->IndexY;

    /* 
    * [origin ť���� �����¿�� �� � ���� �����ִ����� Ȯ��]
    * x�� 0�̸� BottomWall�� �������� �ʴ´�.
    * y�� 0�̸� LeftWall�� �������� �ʴ´�.
    * x�� height-1 �̸� FrontWall �� �������� �ʴ´�.
    * y�� width-1 �̸� RightWall �� �������� �ʴ´�.
    * ���� ����� �ش� ���� ī��Ʈ�� �ʱ�ȭ��Ų��.
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
   * [�������� 4���� ���� �̾��� �ִ°� Ȯ��]
   * if(Front �� �������� �̾��� �ִٸ�)
   *    OriginWall �� ���� ť�� ���� �� �㹮��.
   * if(Bottom �� �������� �̾��� �ִٸ�)
   *    OriginWall �� �Ʒ� ť�� ���� �� �㹮��.
   * if(Right �� �������� �̾��� �ִٸ�)
   *    OriginWall �� ������ ť�� ���� �� �㹮��.
   * if(Left �� �������� �̾��� �ִٸ�)
   *    OriginWall �� ���� ť�� ���� �� �㹮��.
   */
    /*
    * ���� �ڵ�� ������ �ؿ��� ����, ���ʿ��� ���������� �̾����� ���� ��ǥ������ �����ߴ�.
    * ������ ������ �Ʒ���, �����ʿ��� �������� �̾����� �濡 ���ؼ��� shufflenum��ŭ ���ִ°� �ƴ϶�
    * �����־���Ѵ�. �̷��� ��쵵 �߰��ؾ��Ѵ�.
    */
    int32 ShuffleNum = FMath::RandRange(0, 3);
    if (DirectionCountMap[EDirectionWall::Front] >= 4) {
        if(y < PreviousWall->IndexY) {//�������� ���� ����
            if (x + 1 < Height && y + ShuffleNum < Width) {
                MazeGrid[x].Row[y + ShuffleNum]->DeleteOnceWall("Front");
                MazeGrid[x + 1].Row[y + ShuffleNum]->DeleteOnceWall("Bottom");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Front"), x, y + ShuffleNum);
            }
        }
        else { //���������� ���� ����
            if (x + 1 < Height && y - ShuffleNum >= 0) {
                MazeGrid[x].Row[y - ShuffleNum]->DeleteOnceWall("Front");
                MazeGrid[x + 1].Row[y - ShuffleNum]->DeleteOnceWall("Bottom");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Front"), x, y - ShuffleNum);
            }
        }
        DirectionCountMap[EDirectionWall::Front] = 0;
    }
    else if (DirectionCountMap[EDirectionWall::Bottom] >= 4) {
        if (y < PreviousWall->IndexY) {//�������� ���� ����
            if (x - 1 >= 0 && y + ShuffleNum < Width) {
                MazeGrid[x].Row[y + ShuffleNum]->DeleteOnceWall("Bottom");
                MazeGrid[x - 1].Row[y + ShuffleNum]->DeleteOnceWall("Front");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Bottom"), x, y + ShuffleNum);
            }
        }
        else {//���������� ���� ����
            if (x - 1 >= 0 && y - ShuffleNum >= 0) { 
                MazeGrid[x].Row[y - ShuffleNum]->DeleteOnceWall("Bottom"); 
                MazeGrid[x - 1].Row[y - ShuffleNum]->DeleteOnceWall("Front"); 
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Bottom"), x, y - ShuffleNum); 
            }
        }
        DirectionCountMap[EDirectionWall::Bottom] = 0;
    }
    else if (DirectionCountMap[EDirectionWall::Right] >= 4) {
        if (x < PreviousWall->IndexX) {//�Ʒ������� ���� ����
            if (y + 1 < Width && x + ShuffleNum < Height) {
                MazeGrid[x + ShuffleNum].Row[y]->DeleteOnceWall("Right");
                MazeGrid[x + ShuffleNum].Row[y + 1]->DeleteOnceWall("Left");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Right"), x + ShuffleNum, y);
            }
        }
        else {//�������� ���� ����
            if (y + 1 < Width && x - ShuffleNum >= 0) {
                MazeGrid[x - ShuffleNum].Row[y]->DeleteOnceWall("Right");
                MazeGrid[x - ShuffleNum].Row[y + 1]->DeleteOnceWall("Left");
                UE_LOG(LogTemp, Warning, TEXT("4Wall delete MazeGrid[%d][%d] : Right"), x - ShuffleNum, y);
            }
        }
        DirectionCountMap[EDirectionWall::Right] = 0;
    }
    else if (DirectionCountMap[EDirectionWall::Left] >= 4) {
        if (x < PreviousWall->IndexX) {//�Ʒ������� ���� ����
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
