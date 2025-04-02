// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Map/DungeonMap.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/PointLightComponent.h"


constexpr int32 MazeWidth = 19;
constexpr int32 MazeHeight = 19;

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

void ADungeonMap::SetData(TMap<ETileType, TObjectPtr<UStaticMesh>> TileMesh, TMap < ETileType, TObjectPtr<UParticleSystem>> Light)
{
    GeneratorTileMesh = TileMesh;
    GeneratorLight = Light;

    InitializeMaze();

    SpawnMazeTiles();
}

// 랜덤 미로 생성 함수
void ADungeonMap::GenerateMaze(int32 StartX, int32 StartY)
{
    MazeGrid[StartX][StartY] = EMeshType::MT_Ground;

    //수정해야함
    if (bIsStart == false)
    {
        MazeGrid[StartX ][StartY] = EMeshType::MT_Entrance;
        bIsStart = true;
    }

    TArray<int32> RandomDirs = { 0, 1, 2, 3 };
    RandomDirs.Sort([](int32 A, int32 B) { return FMath::RandBool(); }); // 방향 랜덤 섞기

    for (int32 Dir : RandomDirs)
    {
        int32 NextX = StartX + Directions[Dir].X;
        int32 NextY = StartY + Directions[Dir].Y;

        // 미로 범위 내에 있고 아직 방문하지 않은 경우
        if (NextX > 0 && NextX < MazeWidth - 1 && NextY > 0 && NextY < MazeHeight - 1 && MazeGrid[NextX][NextY] == EMeshType::MT_Wall)
        {
            MazeGrid[StartX + Directions[Dir].X / 2][StartY + Directions[Dir].Y / 2] = EMeshType::MT_Ground;

            GenerateMaze(NextX, NextY);
        }
    }
}

// 미로 초기화 및 생성
void ADungeonMap::InitializeMaze()
{
    MazeGrid.SetNum(MazeWidth);
    for (int32 X = 0; X < MazeWidth; X++)
    {
        MazeGrid[X].SetNum(MazeHeight);
        for (int32 Y = 0; Y < MazeHeight; Y++)
        {
            MazeGrid[X][Y] = EMeshType::MT_Wall;
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
                FVector Location = FVector(X * TileSizeX, Y * TileSizeY, 0);
                if (MazeGrid[X][Y] == EMeshType::MT_Entrance)
                {
                    NewTile->SetStaticMesh(GeneratorTileMesh[ETileType::TT_Ground2]);
                    NewTile->SetRelativeLocation(Location);
                    NewTile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
                    NewTile->RegisterComponent();

                    continue;
                }

                NewTile->SetStaticMesh(TileMesh);
                NewTile->SetRelativeLocation(Location);
                NewTile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
                NewTile->RegisterComponent();
            }

            FVector TorchLocation = FVector(X * TileSizeX, Y * TileSizeY, 30);
            FRotator TorchRotator = FRotator(0, 0, 0);
            if (IsCorner(X, Y, TorchLocation, TorchRotator))
            {
                SpawnTorchWithLight(TorchLocation, TorchRotator, ETileType::TT_Torch1, ETileType::TT_Light2);
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
            if (MazeGrid[X][Y] == EMeshType::MT_Wall)
            {
                MakeSperateWall(PlacedWalls, X, Y);
            }
        }
    }  
}

void ADungeonMap::SpawnTorchWithLight(FVector Location, FRotator Rotator, ETileType TorchType, ETileType LightType)
{
    UStaticMeshComponent* NewTorch = NewObject<UStaticMeshComponent>(this);
    UStaticMesh* TorchMesh = GeneratorTileMesh[TorchType];
    if (TorchMesh)
    {
        NewTorch->SetStaticMesh(TorchMesh); // 횃불 메쉬 적용
        NewTorch->SetRelativeLocation(Location);
        NewTorch->SetRelativeRotation(Rotator);
        NewTorch->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
        NewTorch->RegisterComponent();
    }

    UParticleSystemComponent* TorchFire = NewObject<UParticleSystemComponent>(this);
    if (TorchFire)
    {
        UParticleSystem* FireParticle = GeneratorLight[LightType];
        if (FireParticle)
        {
            TorchFire->SetTemplate(FireParticle);
            TorchFire->SetRelativeLocation(FVector(0, 25, 60));
            TorchFire->SetRelativeRotation_Direct(Rotator);
            TorchFire->AttachToComponent(NewTorch, FAttachmentTransformRules::KeepRelativeTransform);
            TorchFire->RegisterComponent();
        }
    }
    UPointLightComponent* TorchLight = NewObject<UPointLightComponent>(this);
    if (TorchLight)
    {
        TorchLight->SetIntensity(5000.0f);  // 광원 밝기 설정
        TorchLight->SetLightColor(FLinearColor(1.0f, 0.5f, 0.2f));  // 주황빛
        TorchLight->SetAttenuationRadius(300.0f); // 광원 범위
        TorchLight->SetRelativeLocation(FVector(0, 0, 100)); // 살짝 위로 배치
        TorchLight->AttachToComponent(TorchFire, FAttachmentTransformRules::KeepRelativeTransform);
        TorchLight->RegisterComponent();
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

bool ADungeonMap::IsCorner(int32 X, int32 Y, FVector& OutLocationOffset, FRotator& OutRotatorOffset)
{
    if (MazeGrid[X][Y] != EMeshType::MT_Ground)
        return false;

    if (X <= 0 || X >= MazeWidth - 1 || Y <= 0 || Y >= MazeHeight - 1)
        return false;

    struct CornerCheck
    {
        int32 DX1, DY1, DX2, DY2;
        FVector LocationOffset;
        FRotator RotatorOffset;
    };

    struct EndOpenCheck
    {
        int32 DX1, DY1, DX2, DY2, DX3, DY4;
        FVector LocationOffset;
        FRotator RotatorOffset;
    };

    const EndOpenCheck EndOpenTiles[] = {

    {  0, -1,  1,  0,  0,  1, FVector(-80, 0, 0), FRotator(0, 270 ,0)},    // 좌단
    {  1,  0,  0,  1, -1,  0, FVector(0, -80, 0), FRotator(0, 0, 0)},      // 상단
    {  0,  1, -1,  0,  0, -1, FVector(80, 0, 0), FRotator(0, 90, 0)},      // 우단
    { -1,  0,  0, -1,  1,  0, FVector(0, 80, 0), FRotator(0, 180 ,0)},     // 하단
    };

    const CornerCheck Corners[] = {

        {  0, -1, -1,  0, FVector(-50, -80, 0), FRotator(0, 0 ,0)},   // 좌하단
        { -1,  0,  0,  1, FVector(-80, 50, 0), FRotator(0, 270 ,0)},  // 좌상단
        {  0,  1,  1,  0, FVector(50, 80, 0), FRotator(0, 180 ,0)},   // 우상단
        {  1,  0,  0, -1, FVector(80, -50, 0), FRotator(0, 90 ,0)},   // 우하단
    };

    for (const EndOpenCheck& EndOpen : EndOpenTiles)
    {
        if (MazeGrid[X + EndOpen.DX1][Y + EndOpen.DY1] == EMeshType::MT_Ground &&
            MazeGrid[X + EndOpen.DX2][Y + EndOpen.DY2] == EMeshType::MT_Ground &&
            MazeGrid[X + EndOpen.DX3][Y + EndOpen.DY4] == EMeshType::MT_Ground)
        {
            OutLocationOffset = OutLocationOffset + EndOpen.LocationOffset;
            OutRotatorOffset = EndOpen.RotatorOffset;
            return true;
        }

        if (MazeGrid[X + EndOpen.DX1][Y + EndOpen.DY1] == EMeshType::MT_Wall &&
            MazeGrid[X + EndOpen.DX2][Y + EndOpen.DY2] == EMeshType::MT_Wall &&
            MazeGrid[X + EndOpen.DX3][Y + EndOpen.DY4] == EMeshType::MT_Wall)
        {
            OutLocationOffset = OutLocationOffset - EndOpen.LocationOffset;
            OutRotatorOffset = EndOpen.RotatorOffset + FRotator(0, 180, 0);
            return true;
        }
    }

    for (const CornerCheck& Corner : Corners)
    {
        if (MazeGrid[X + Corner.DX1][Y + Corner.DY1] == EMeshType::MT_Wall &&
            MazeGrid[X + Corner.DX2][Y + Corner.DY2] == EMeshType::MT_Wall)
        {
            OutLocationOffset = OutLocationOffset + Corner.LocationOffset;
            OutRotatorOffset = Corner.RotatorOffset;
            return true;
        }
    }

    return false;
}
