// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"

#include "ExitTrigger.generated.h"

UCLASS()
class RANDOMMAP_API AExitTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExitTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void NotifyActorBeginOverlap(AActor* OtherActor) override;


private:
	UPROPERTY()
	UBoxComponent* TriggerZone;
};
