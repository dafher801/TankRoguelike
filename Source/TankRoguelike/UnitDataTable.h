
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorDataTable.h"
#include "UnitDataTable.generated.h"

USTRUCT()
struct FUnitData : public FActorData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitData")
		int Score;
};

UCLASS()
class TANKROGUELIKE_API UUnitDataTable : public UActorDataTable
{
	GENERATED_BODY()
};
