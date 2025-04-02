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
			if (Row->TileMesh.Len() > 0)
			{
				UStaticMesh* LoadedMesh = LoadObject<UStaticMesh>(nullptr, *Row->TileMesh);
				if (LoadedMesh)
				{
					ETileType tileType = ConvertStringToEnum(Row->TileType);

					MeshData.Add(tileType, LoadedMesh);
				}
			}

			if (Row->LightParticle.Len() > 0)
			{
				UParticleSystem* LoadedLight = LoadObject<UParticleSystem>(nullptr, *Row->LightParticle);
				if (LoadedLight)
				{
					ETileType tileType = ConvertStringToEnum(Row->TileType);

					LightData.Add(tileType, LoadedLight);
				}
			}
		}
	}
}

ETileType UMazeGeneratorSubSystem::ConvertStringToEnum(const FString& TypeString)
{
	UEnum* EnumPtr = StaticEnum<ETileType>();
	if (!EnumPtr) return ETileType::END;
	if (!EnumPtr)
		return ETileType::END; // 예외 처리

	int32 EnumValue = EnumPtr->GetValueByName(FName(*TypeString));
	if (EnumValue == INDEX_NONE)
		return ETileType::END;

	return static_cast<ETileType>(EnumValue);
}