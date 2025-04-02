// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/MazeGeneratorManager.h"

UMazeGeneratorManager* UMazeGeneratorManager::Instance = nullptr;

UMazeGeneratorManager::UMazeGeneratorManager()
{
	
}
void UMazeGeneratorManager::GenerateMap()
{
	if (CurrentMap)
		DestroyCurrentMap();

	ADungeonMap* DungeonMap = GetWorld()->SpawnActor<ADungeonMap>(ADungeonMap::StaticClass());
	if (DungeonMap)
	{
		UE_LOG(LogTemp, Log, TEXT("MapGenerator created successfully."));
	}
	
	UMazeGeneratorSubSystem* MazeSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMazeGeneratorSubSystem>();
	if (MazeSubsystem)
	{
		TMap<ETileType, TObjectPtr<UStaticMesh>> TileMesh = MazeSubsystem->GetMeshFromTable();
		TMap<ETileType, TObjectPtr<UParticleSystem>> LightParticle = MazeSubsystem->GetLightFromTable();

		DungeonMap->SetData(TileMesh, LightParticle);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MazeGeneratorSubSystem is not available."));
	}
}

void UMazeGeneratorManager::DestroyCurrentMap()
{
	if (CurrentMap)
	{
		CurrentMap->Destroy();
		CurrentMap = nullptr;
	}
}

