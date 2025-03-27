// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DataTable/TileResourceData.h"

#include "DungeonMap.generated.h"

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
	void SetData(TMap<ETileType, TObjectPtr<UStaticMesh>> TileMesh);
	void GenerateMaze(int32 StartX, int32 StartY);
	void InitializeMaze();

	void SpawnMazeTiles();
	void SpawnMazeWalls();

	void MakeSperateWall(TSet<FVector>& PlacedWalls, int32 X, int32 Y);


private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY()
	TMap<ETileType, TObjectPtr<UStaticMesh>> GeneratorTileMesh;

	// 미로 데이터 저장 (0 = 길, 1 = 벽, 2 = 입구, 3 = 출구)
	TArray<TArray<int32>> MazeGrid;

	bool bIsStart = false;
};
