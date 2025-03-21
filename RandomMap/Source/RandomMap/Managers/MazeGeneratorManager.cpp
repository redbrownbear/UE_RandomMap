// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/MazeGeneratorManager.h"

UMazeGeneratorManager* UMazeGeneratorManager::Instance = nullptr;

UMazeGeneratorManager::UMazeGeneratorManager()
{
	
}
void UMazeGeneratorManager::GenerateMap()
{
	if (CurrentMapGenerator) 
		DestroyGenerator(); 
	
	if (CurrentMap)
		DestroyCurrentMap();


	// 맵 생성기 생성
	AMazeGenerator* MapGenerator = NewObject<AMazeGenerator>();
	
	UMazeGeneratorSubSystem* MazeSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMazeGeneratorSubSystem>();
	if (MazeSubsystem)
	{
		TMap<ETileType, TObjectPtr<UStaticMesh>> TileMesh = MazeSubsystem->GetMeshFromTable();
		TMap<ETileType, TObjectPtr<UMaterialInterface>> TileMaterial = MazeSubsystem->GetMaterialFromTable();


		MapGenerator->SetData(TileMesh, TileMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MazeGeneratorSubSystem is not available."));
	}
}

void UMazeGeneratorManager::DestroyGenerator()
{
	if (CurrentMapGenerator)
	{
		CurrentMapGenerator->Destroy();
		CurrentMapGenerator = nullptr;
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

