// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Map/DungeonMap.h"


constexpr int32 MazeWidth = 29;
constexpr int32 MazeHeight = 29;

constexpr int32 TileSizeX = 200;
constexpr int32 TileSizeY = 200;

constexpr int32 WallSizeZ = 150;

const FVector2D Directions[4] = { FVector2D(0, -2), FVector2D(0, 2), FVector2D(-2, 0), FVector2D(2, 0) };

const FVector Offsets[4] = {
FVector(TileSizeX / 2, 0, 0),  // 동쪽 벽
FVector(-TileSizeX / 2, 0, 0), // 서쪽 벽
FVector(0, TileSizeY / 2, 0),  // 북쪽 벽
FVector(0, -TileSizeY / 2, 0)  // 남쪽 벽
};

// Sets default values
ADungeonMap::ADungeonMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    RootComponent = DefaultSceneRoot;

}

// Called when the game starts or when spawned
void ADungeonMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADungeonMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonMap::SetData(TMap<ETileType, TObjectPtr<UStaticMesh>> TileMesh)
{
    GeneratorTileMesh = TileMesh;

    InitializeMaze();

    SpawnMazeTiles();
}

// 랜덤 미로 생성 함수
void ADungeonMap::GenerateMaze(int32 StartX, int32 StartY)
{
    MazeGrid[StartX][StartY] = 0;

    if (bIsStart == false)
    {
        MazeGrid[StartX ][StartY] = 2;
        bIsStart = true;
    }

    TArray<int32> RandomDirs = { 0, 1, 2, 3 };
    RandomDirs.Sort([](int32 A, int32 B) { return FMath::RandBool(); }); // 방향 랜덤 섞기

    for (int32 Dir : RandomDirs)
    {
        int32 NextX = StartX + Directions[Dir].X;
        int32 NextY = StartY + Directions[Dir].Y;

        // 미로 범위 내에 있고 아직 방문하지 않은 경우
        if (NextX > 0 && NextX < MazeWidth - 1 && NextY > 0 && NextY < MazeHeight - 1 && MazeGrid[NextX][NextY] == 1)
        {
            MazeGrid[StartX + Directions[Dir].X / 2][StartY + Directions[Dir].Y / 2] = 0;

            GenerateMaze(NextX, NextY);
        }
    }
}

// 미로 초기화 및 생성
void ADungeonMap::InitializeMaze()
{
    // 미로 초기화 (벽으로 채우기)
    MazeGrid.SetNum(MazeWidth);
    for (int32 X = 0; X < MazeWidth; X++)
    {
        MazeGrid[X].SetNum(MazeHeight);
        for (int32 Y = 0; Y < MazeHeight; Y++)
        {
            MazeGrid[X][Y] = 1;
        }
    }

    GenerateMaze(1, 1);
}

// 미로를 타일로 변환하여 생성
void ADungeonMap::SpawnMazeTiles()
{
    for (int32 X = 0; X < MazeWidth; X++)
    {
        for (int32 Y = 0; Y < MazeHeight; Y++)
        {
            UStaticMeshComponent* NewTile = NewObject<UStaticMeshComponent>(this);
            UStaticMesh* TileMesh = GeneratorTileMesh[ETileType::TT_Ground1];

            if (TileMesh)
            {
                if (MazeGrid[X][Y] == 2)
                {
                    NewTile->SetStaticMesh(GeneratorTileMesh[ETileType::TT_Ground2]);
                    NewTile->SetRelativeLocation(FVector(X * TileSizeX, Y * TileSizeY, 0));
                    NewTile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
                    NewTile->RegisterComponent();

                    continue;
                }

                NewTile->SetStaticMesh(TileMesh);
                NewTile->SetRelativeLocation(FVector(X * TileSizeX, Y * TileSizeY, 0));
                NewTile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
                NewTile->RegisterComponent();
            }
        }
    }

    SpawnMazeWalls();
}

void ADungeonMap::SpawnMazeWalls()
{
    TSet<FVector> PlacedWalls; // 중복 생성 방지용

    for (int32 X = 0; X < MazeWidth; X++)
    {
        for (int32 Y = 0; Y < MazeHeight; Y++)
        {
            if (MazeGrid[X][Y] == 1)
            {
                MakeSperateWall(PlacedWalls, X, Y);
            }
        }
    }  
}

void ADungeonMap::MakeSperateWall(TSet<FVector>& PlacedWalls, int32 X, int32 Y)
{
    for (int32 Dir = 0; Dir < 4; ++Dir)
    {      
        {
            FVector WallLocation = FVector(TileSizeX * X, TileSizeY * Y, -30) + Offsets[Dir];

            if (!PlacedWalls.Contains(WallLocation))
            {
                UStaticMeshComponent* NewWall = NewObject<UStaticMeshComponent>(this);
                UStaticMesh* WallMesh = GeneratorTileMesh[ETileType::TT_Wall1];

                if (WallMesh)
                {
                    NewWall->SetStaticMesh(WallMesh);
                    NewWall->SetRelativeScale3D(FVector(0.32, 0.32, 1));
                    NewWall->SetRelativeLocation(WallLocation);
                    NewWall->SetRelativeRotation((Dir == 0 || Dir == 1) ? FRotator(0, 90, 0) : FRotator(0, 0, 0));
                    NewWall->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
                    NewWall->RegisterComponent();

                    PlacedWalls.Add(WallLocation);
                }
            }
        }
    }
}
