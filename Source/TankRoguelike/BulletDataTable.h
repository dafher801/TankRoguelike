
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorDataTable.h"
#include "BulletDataTable.generated.h"

USTRUCT()
struct FBulletData : public FActorData
{
	GENERATED_BODY()
};

UCLASS()
class TANKROGUELIKE_API ABulletDataTable : public AActorDataTable
{
	GENERATED_BODY()
};
