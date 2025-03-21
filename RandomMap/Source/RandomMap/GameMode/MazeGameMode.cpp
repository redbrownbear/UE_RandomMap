// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MazeGameMode.h"
#include "Actors/Map/MazeGenerator.h"
#include "Managers/MazeGeneratorManager.h"

void AMazeGameMode::BeginPlay()
{
	Super::BeginPlay();


	auto Manager = UMazeGeneratorManager::GetInstance();
	if (Manager)
	{
		Manager->GenerateMap();
	}
}
