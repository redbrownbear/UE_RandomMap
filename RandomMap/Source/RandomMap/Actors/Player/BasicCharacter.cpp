// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Player/BasicCharacter.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(CollisionProfileName::Player);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasicCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ABasicCharacter::SetData(EPlayerType PlayerType)
{
	UPlayerManagementSubSystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerManagementSubSystem>();
	if (Subsystem)
	{
		FPlayerResourceData* PlayerResourceData = Subsystem->GetPlayerResourceData(PlayerType);
		if (PlayerResourceData)
		{	
			UCapsuleComponent* Capsule = GetCapsuleComponent();
			if (!FMath::IsNearlyEqual(Capsule->GetUnscaledCapsuleHalfHeight(), PlayerResourceData->CollisionCapsuleHalfHeight))
			{
				Capsule->SetCapsuleHalfHeight(PlayerResourceData->CollisionCapsuleHalfHeight, false);
			}
		
		
			USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
			SkeletalMeshComponent->SetSkeletalMesh(PlayerResourceData->SkeletalMesh.Get());
			SkeletalMeshComponent->SetRelativeTransform(FTransform::Identity);
			SkeletalMeshComponent->SetWorldLocation(FVector(200.0, 200.0, 0));
			SkeletalMeshComponent->SetWorldRotation(FRotator(180.0, 180.0, 180.0));

			//SkeletalMeshComponent->SetAnimClass(CharacterData->AnimClass);
		}
	}
}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

