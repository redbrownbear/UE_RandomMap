// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "DataTable/PlayerresourceData.h"

#include "PlayerManagementSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class RANDOMMAP_API UPlayerManagementSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPlayerManagementSubSystem();

public:
	void LoadTable();

public:
	FPlayerResourceData* GetPlayerResourceData(EPlayerType PlayerType);


private:
	UPROPERTY(EditAnywhere, Category = "PlayerResource")
	UDataTable* DataTable;

	UPROPERTY()
	TArray<FPlayerResourceData> PlayerResourceDataTable;
};