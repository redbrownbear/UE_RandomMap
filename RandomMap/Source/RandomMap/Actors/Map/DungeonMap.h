// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DataTable/TileResourceData.h"

#include "DungeonMap.generated.h"


enum EMeshType : uint8
{
	MT_Ground,
	MT_Entrance,
	MT_Exit,
	MT_Wall,
	MT_Torch,
	
	END,
};

UCLASS()
class RANDOMMAP_API ADungeonMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetData(TMap<ETileType, TObjectPtr<UStaticMesh>> TileMesh, TMap < ETileType, TObjectPtr<UParticleSystem>> Light);
	void GenerateMaze(int32 StartX, int32 StartY);
	void InitializeMaze();

	void SpawnMazeTiles();
	void SpawnMazeWalls();
	void SpawnTorchWithLight(FVector Location, FRotator Rotator, ETileType TorchType, ETileType LightType);

	void MakeSperateWall(TSet<FVector>& PlacedWalls, int32 X, int32 Y);

private:
	bool IsCorner(int32 X, int32 Y, FVector& OutLocationOffset, FRotator& OutRotatorOffset);

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY()
	TMap<ETileType, TObjectPtr<UStaticMesh>> GeneratorTileMesh;

	UPROPERTY()
	TMap < ETileType, TObjectPtr<UParticleSystem>> GeneratorLight;

	TArray<TArray<EMeshType>> MazeGrid;

	bool bIsStart = false;
};
