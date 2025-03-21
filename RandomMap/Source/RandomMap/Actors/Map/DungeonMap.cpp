// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Map/DungeonMap.h"

// Sets default values
ADungeonMap::ADungeonMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADungeonMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

