// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Map/DungeonMap.h"

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

    GenrateMaze();
}

void ADungeonMap::GenrateMaze()
{
    int32 GridSizeX = 10;
    int32 GridSizeY = 10;

    for (int32 X = 0; X < GridSizeX; X++)
    {
        for (int32 Y = 0; Y < GridSizeY; Y++)
        {
            if (GeneratorTileMesh.Contains(ETileType::TT_Ground1))
            {
                UStaticMeshComponent* NewTile = NewObject<UStaticMeshComponent>(this);
                UStaticMesh* TileMesh = GeneratorTileMesh[ETileType::TT_Ground1];

                if (TileMesh)
                {
                    NewTile->SetStaticMesh(TileMesh);

                    FBoxSphereBounds Bounds = TileMesh->GetBounds();
                    FVector BoxExtent = Bounds.BoxExtent;

                    NewTile->SetRelativeLocation(FVector(X * BoxExtent.X * 2.0f, Y * BoxExtent.Y * 2.0f, 0));
                    NewTile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
                    NewTile->RegisterComponent();
                }
            }
        }
    }
}

