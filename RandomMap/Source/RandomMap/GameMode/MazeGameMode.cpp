// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MazeGameMode.h"
#include "Managers/MazeGeneratorManager.h"

void AMazeGameMode::StartPlay()
{
	Super::StartPlay();

	//temp
	{
		UMazeGeneratorManager* mazeManager = NewObject<UMazeGeneratorManager>(this);
		{
			mazeManager->Initialize(GetWorld());
			mazeManager->GenerateMap();
		}
	}
}
