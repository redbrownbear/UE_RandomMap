// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Trigger/ExitTrigger.h"
#include "Misc/Utils.h"

#include "Actors/Player/BasicCharacter.h"

// Sets default values
AExitTrigger::AExitTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerZone;
	TriggerZone->SetBoxExtent(FVector(200.f, 200.f, 100.f));
	TriggerZone->SetCollisionProfileName(CollisionProfileName::Player);
}

// Called when the game starts or when spawned
void AExitTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExitTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExitTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (Cast<ABasicCharacter>(OtherActor)) 
	{
		// 게임 종료 처리 또는 다음 레벨 전환

		GEngine->AddOnScreenDebugMessage(
			-1,                          // Key (고유 ID, -1은 항상 새 메시지)
			5.0f,                        // Duration (초)
			FColor::Green,              // 색깔
			TEXT("출구 도달!")          // 메시지 내용
		);
	}

}

