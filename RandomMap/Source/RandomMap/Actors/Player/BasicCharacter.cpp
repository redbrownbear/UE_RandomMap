// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Player/BasicCharacter.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(CollisionProfileName::Player);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	const FRotator Rotation = FRotator(0., 0.0, 0.);
	const FVector Translation = FVector(20.0, 0.0, 150.0);
	FTransform CameraTransform = FTransform(Rotation, Translation, FVector::OneVector);
	Camera->SetRelativeTransform(CameraTransform);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasicCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetData(EPlayerType::PT_One);
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
			SkeletalMeshComponent->SetSkeletalMesh(PlayerResourceData->SkeletalMesh);
			SkeletalMeshComponent->SetRelativeTransform(FTransform::Identity);
			SkeletalMeshComponent->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
			
			SkeletalMeshComponent->SetVisibility(false);
			SkeletalMeshComponent->bCastHiddenShadow = true;
			

			//SkeletalMeshComponent->SetAnimClass(CharacterData->AnimClass);
			
			//SkeletalMeshComponent->bOwnerNoSee = true;
		}
	}

	{
		UCharacterMovementComponent* Movement = GetCharacterMovement();
		Movement->bOrientRotationToMovement = true;
		Movement->MaxWalkSpeed = 500.0;
	}

	{
		this->SetActorLocation(FVector(200.0, 200.0, 3000.0));

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

