// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MazeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RANDOMMAP_API AMazeGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
};
