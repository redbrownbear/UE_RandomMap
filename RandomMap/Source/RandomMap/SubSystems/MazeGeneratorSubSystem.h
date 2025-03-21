// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataTable/TileResourceData.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"

#include "MazeGeneratorSubSystem.generated.h"

/**
 * 
 */

UCLASS()
class RANDOMMAP_API UMazeGeneratorSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:
	UMazeGeneratorSubSystem();

	void LoadTable();

public:
	const TMap<ETileType, TObjectPtr<UStaticMesh>> GetMeshFromTable() { return MeshData; }

	const TMap<ETileType, TObjectPtr<UMaterialInterface>> GetMaterialFromTable() { return MaterialData;}

private:
	UPROPERTY(EditAnywhere, Category = "ResourceTile")
	UDataTable* ItemDataTable;

	UPROPERTY()
	TMap<ETileType, TObjectPtr<UStaticMesh>> MeshData;

	UPROPERTY()
	TMap<ETileType, TObjectPtr<UMaterialInterface>> MaterialData;
};
