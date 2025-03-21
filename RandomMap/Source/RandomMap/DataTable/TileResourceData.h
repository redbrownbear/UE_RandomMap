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

    END,
};

ENUM_RANGE_BY_COUNT(ETileType, ETileType::END);

USTRUCT(BlueprintType)  // 블루프린트에서 사용 가능하도록 설정
struct FTileResourceData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    ETileType TileType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    FString TileMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
    FString TileMaterial;
};