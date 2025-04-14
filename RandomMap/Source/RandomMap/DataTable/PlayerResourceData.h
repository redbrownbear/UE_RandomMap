// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

#include "PlayerResourceData.generated.h"


UENUM(BlueprintType)
enum class EPlayerType : uint8
{
	None,

	PT_One UMETA(DisplayName = "One"),
	PT_Two UMETA(DisplayName = "Two"),

	END,
};

USTRUCT(BlueprintType)
struct FPlayerResourceData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "PlayerMesh")
	EPlayerType PlayerType;

	UPROPERTY(EditAnywhere, Category = "PlayerMesh")
	USkeletalMesh* SkeletalMesh;

public:
	UPROPERTY(EditAnywhere, Category = "Animation")
	FString AnimClass;
	//UPROPERTY(EditAnywhere, Category = "Animation")
	//TArray<UAnimMontage*> HitReactMontage;
	//UPROPERTY(EditAnywhere, Category = "Animation")
	//TArray<UAnimMontage*> DieMontage;

public:
	UPROPERTY(EditAnywhere, Category = "Collision")
	float CollisionSphereRadius;
	UPROPERTY(EditAnywhere, Category = "Collision")
	float CollisionCapsuleRadius;
	UPROPERTY(EditAnywhere, Category = "Collision")
	float CollisionCapsuleHalfHeight;
	UPROPERTY(EditAnywhere, Category = "Collision")
	FVector CollisionBoxExtent;
};