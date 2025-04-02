#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "TileResourceData.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
    TT_Ground1 UMETA(DisplayName = "Ground1"),
    TT_Ground2 UMETA(DisplayName = "Ground2"),
    TT_Ground3 UMETA(DisplayName = "Ground3"),
    TT_Wall1  UMETA(DisplayName = "Wall1"),
    TT_Wall2  UMETA(DisplayName = "Wall2"),
    TT_Wall3  UMETA(DisplayName = "Wall3"),
    TT_Torch1 UMETA(DisplayName = "Torch1"),
    TT_Torch2 UMETA(DisplayName = "Torch2"),
    TT_Torch3 UMETA(DisplayName = "Torch3"),
    TT_Light1 UMETA(DisplayName = "Light1"),
    TT_Light2 UMETA(DisplayName = "Light2"),
    TT_Light3 UMETA(DisplayName = "Light3"),

    END,
};

USTRUCT(BlueprintType)
struct FTileResourceData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Tile")
    FString TileType;

    UPROPERTY(EditAnywhere, Category = "Tile")
    FString TileMesh;

    UPROPERTY(EditAnywhere, Category = "Tile")
    FString LightParticle;
};