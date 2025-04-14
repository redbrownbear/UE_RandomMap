// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/PlayerManagementSubSystem.h"

UPlayerManagementSubSystem::UPlayerManagementSubSystem()
{
	LoadTable();
}

void UPlayerManagementSubSystem::LoadTable()
{
	if (!DataTable)
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Data/PlayerResourceDataTable.PlayerResourceDataTable'"));
		check(Asset.Object);
		DataTable = Asset.Object;
	}

	// 데이터 테이블을 통해 아이템 리소스를 초기화
	if (DataTable)
	{
		TArray<FPlayerResourceData> PlayerResourceDataArray;

		if (DataTable)
		{
			// 데이터 테이블의 모든 행 가져오기
			for (const auto& Row : DataTable->GetRowMap())
			{
				FPlayerResourceData* PlayerResourceData = (FPlayerResourceData*)Row.Value;
				if (PlayerResourceData)
				{
					PlayerResourceDataArray.Add(*PlayerResourceData);
				}
			}

			PlayerResourceDataTable = PlayerResourceDataArray;
		}
	}
}

FPlayerResourceData* UPlayerManagementSubSystem::GetPlayerResourceData(EPlayerType PlayerType)
{
	for (FPlayerResourceData& PlayerResource : PlayerResourceDataTable)
	{
		if (PlayerResource.PlayerType == PlayerType)
		{
			return &PlayerResource;
		}
	}
	
	return nullptr;
}
