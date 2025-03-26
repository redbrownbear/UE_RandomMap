// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DataTable/TileResourceData.h"
#include "SubSystems/MazeGeneratorSubSystem.h"

#include "Actors/Map/DungeonMap.h"

#include "MazeGeneratorManager.generated.h"

/**
 * 
 */
UCLASS()
class RANDOMMAP_API UMazeGeneratorManager : public UObject
{
	GENERATED_BODY()
	
protected:
	UMazeGeneratorManager();

public:
	static UMazeGeneratorManager* GetInstance()
	{
		if (!Instance)
		{
			Instance = NewObject<UMazeGeneratorManager>();
			Instance->AddToRoot();
		}

		return Instance;
	}

public:
	//제너레이터 관련
	void GenerateMap();
	//void CompleteStage();

	void DestroyCurrentMap();

public:
	UWorld* GetWorld() const override { return WorldContext; }

	void Initialize(UWorld* InWorld) { WorldContext = InWorld; }

private:
	static UMazeGeneratorManager* Instance;

	UPROPERTY()
	UWorld* WorldContext;

	UPROPERTY()
	ADungeonMap* CurrentMap;
};