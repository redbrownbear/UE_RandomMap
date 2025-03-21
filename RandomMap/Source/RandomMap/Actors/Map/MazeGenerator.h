// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DataTable/TileResourceData.h"

#include "Actors/Map/DungeonMap.h"

#include "MazeGenerator.generated.h"

UCLASS()
class RANDOMMAP_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	void SetData(TMap<ETileType, TObjectPtr<UStaticMesh>> TileMesh, TMap<ETileType, TObjectPtr<UMaterialInterface>> TileMaterial);
	
public:
	void GenrateMaze();


private:
	UPROPERTY()
	TMap<ETileType, TObjectPtr<UStaticMesh>> GeneratorTileMesh;

	UPROPERTY()
	TMap<ETileType, TObjectPtr<UMaterialInterface>> GeneratorTileMaterial;

	UPROPERTY()
	TMap<ETileType, UStaticMeshComponent*> TileMeshComponents;
};
