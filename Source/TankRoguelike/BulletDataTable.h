
#pragma once

#include "CoreMinimal.h"
#include "ActorDataTable.h"
#include "BulletDataTable.generated.h"

USTRUCT()
struct FBulletData : public FActorData
{
	GENERATED_BODY()
};

UCLASS()
class TANKROGUELIKE_API UBulletDataTable : public UActorDataTable
{
	GENERATED_BODY()
};
