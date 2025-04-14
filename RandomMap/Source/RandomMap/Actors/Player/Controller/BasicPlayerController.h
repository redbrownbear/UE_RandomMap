// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"

#include "Misc/Utils.h"

#include "BasicPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RANDOMMAP_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
	ABasicPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	/**
	 * Overridable native function for when this controller is asked to possess a pawn.
	 * @param InPawn The Pawn to be possessed
	 */
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	void OnChangeRotator(const FInputActionValue& InputActionValue);
	void OnMove(const FInputActionValue& InputActionValue);

	//void OnRun(const FInputActionValue& InputActionValue);
	//void OnEndRun(const FInputActionValue& InputActionValue);

	//void OnInterAct(const FInputActionValue& InputActionValue);

public:
	const FVector2D& GetMoveInputActionVector() { return InputMoveActionVector; }


protected:
	UInputMappingContext* IMC_Default = nullptr;

	UPROPERTY(BlueprintReadWrite)
	bool bIsAiming = false;

	//UPROPERTY()
	//class UStatusComponent* StatusComponent;

	UPROPERTY()
	FVector2D InputMoveActionVector;
};
