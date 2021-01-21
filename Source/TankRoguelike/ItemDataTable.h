
#pragma once

#include "CoreMinimal.h"
#include "ActorDataTable.h"
#include "ItemDataTable.generated.h"

USTRUCT()
struct FItemData : public FActorData
{
	GENERATED_BODY()

};

UCLASS()
class TANKROGUELIKE_API AItemDataTable : public AActorDataTable
{
	GENERATED_BODY()
	
};
