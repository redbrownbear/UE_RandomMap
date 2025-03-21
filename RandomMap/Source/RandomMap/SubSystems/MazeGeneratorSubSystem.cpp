// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/MazeGeneratorSubSystem.h"
#include "Managers/MazeGeneratorManager.h"

UMazeGeneratorSubSystem::UMazeGeneratorSubSystem()
{
	LoadTable();
}

void UMazeGeneratorSubSystem::LoadTable()
{
	if (!ItemDataTable)
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Data/TileDataTable.TileDataTable'"));
		check(Asset.Object);
		ItemDataTable = Asset.Object;
	}

	// 데이터 테이블을 통해 아이템 리소스를 초기화
	if (ItemDataTable)
	{
		// 테이블에서 각 행을 가져옴
		TArray<FTileResourceData*> AllRows;
		ItemDataTable->GetAllRows(TEXT("GetAllRows"), AllRows);

		for (FTileResourceData* Row : AllRows)
		{
			// 메시와 머티리얼 경로를 가져와서 풀에 저장
			if (Row->TileMesh.Len() > 0)
			{
				UStaticMesh* LoadedMesh = LoadObject<UStaticMesh>(nullptr, *Row->TileMesh);
				if (LoadedMesh)
				{
					MeshData.Add(Row->TileType, LoadedMesh);
				}
			}

			if (Row->TileMaterial.Len() > 0)
			{
				UMaterialInterface* LoadedMaterial = LoadObject<UMaterialInterface>(nullptr, *Row->TileMaterial);
				if (LoadedMaterial)
				{
					MaterialData.Add(Row->TileType, LoadedMaterial);
				}
			}
		}
	}

	
	//auto Manager = UMazeGeneratorManager::GetInstance();
	//if (Manager)
	//{
	//	Manager->GenerateMap();
	//}
}