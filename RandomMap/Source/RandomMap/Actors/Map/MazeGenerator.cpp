// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Map/MazeGenerator.h"

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
	
}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeGenerator::SetData(TMap<ETileType, TObjectPtr<UStaticMesh>> TileMesh, TMap<ETileType, TObjectPtr<UMaterialInterface>> TileMaterial)
{
	GeneratorTileMesh = TileMesh;
	GeneratorTileMaterial = TileMaterial;

    GenrateMaze();
}

void AMazeGenerator::GenrateMaze()
{
	ADungeonMap* DungeonMap = NewObject<ADungeonMap>();
	if (!DungeonMap)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create DungeonMap"));
        return;
    }

    UWorld* World = GetWorld();
    if (World)
    {
        DungeonMap->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
        DungeonMap->SetActorRotation(FRotator::ZeroRotator);

        UStaticMeshComponent* MapRootComponent = NewObject<UStaticMeshComponent>(DungeonMap);
        MapRootComponent->SetupAttachment(DungeonMap->GetRootComponent()); 
        MapRootComponent->RegisterComponent();

        // 메시와 머터리얼 설정 (예: 바닥 메시와 벽 메시)
        if (GeneratorTileMesh.Contains(ETileType::TT_Ground1) && GeneratorTileMaterial.Contains(ETileType::TT_Ground1))
        {
            MapRootComponent->SetStaticMesh(GeneratorTileMesh[ETileType::TT_Ground1]);
            MapRootComponent->SetMaterial(0, GeneratorTileMaterial[ETileType::TT_Ground1]);
        }

        World->SpawnActor<ADungeonMap>(DungeonMap->GetClass(), DungeonMap->GetActorLocation(), DungeonMap->GetActorRotation());

        // 추가적인 맵 설정 (예: 벽과 바닥, 장애물 등을 DungeonMap에 추가)
        // Add additional mesh components for walls, floor, and other elements based on your map data
    }
}