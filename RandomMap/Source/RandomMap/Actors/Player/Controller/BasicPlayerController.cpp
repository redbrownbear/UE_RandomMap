// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Player/Controller/BasicPlayerController.h"
#include "Actors/Player/BasicCharacter.h"

#include "Kismet/KismetMathLibrary.h"

#include "GameFramework/CharacterMovementComponent.h"

ABasicPlayerController::ABasicPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
	{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/BluePrints/Input/Player/IMC_Maze.IMC_Maze'") };
	check(Asset.Object);

	IMC_Default = Asset.Object;

}
void ABasicPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(IMC_Default, 0);

	// 컨트롤러에 의해 캐릭터가 회전하도록 설정 (Yaw 회전만)a
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		ControlledPawn->bUseControllerRotationYaw = true;  // 캐릭터가 컨트롤러의 회전을 따름
		UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(ControlledPawn->GetMovementComponent());
		if (MovementComponent)
		{
			MovementComponent->bOrientRotationToMovement = false;  // 이동 방향으로 회전하지 않음
		}
	}

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
}

void ABasicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_Move")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Move is disabled"));
	}

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_Default, TEXT("IA_ChangeRotator")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnChangeRotator);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_ChangeRotator is disabled"));
	}

}

void ABasicPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void ABasicPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABasicPlayerController::OnChangeRotator(const FInputActionValue& InputActionValue)
{
	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();

	AddYawInput(ActionValue.X);
	AddPitchInput(-ActionValue.Y);

	//ControlRotation.Pitch = FMath::Clamp(ControlRotation.Pitch - ActionValue.Y, -80.f, 80.f);
}

void ABasicPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = K2_GetActorRotation();
	const FRotator RotationYaw = FRotator(0.0, Rotation.Yaw, 0.0);
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(RotationYaw);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(RotationYaw);

	ABasicCharacter* ControlledCharacter = Cast<ABasicCharacter>(GetPawn());
	ControlledCharacter->AddMovementInput(ForwardVector, ActionValue.X);
	ControlledCharacter->AddMovementInput(RightVector, ActionValue.Y);

	InputMoveActionVector = ActionValue;
}
