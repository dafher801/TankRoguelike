
#pragma once

#include "CoreMinimal.h"
#include "ActorDataTable.h"
#include "WeaponDataTable.generated.h"

USTRUCT()
struct FWeaponData : public FActorData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Weapon")
		int MaxBulletNum;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		FRotator RevisedFireRotation;
};

UCLASS()
class TANKROGUELIKE_API UWeaponDataTable : public UActorDataTable
{
	GENERATED_BODY()
};
