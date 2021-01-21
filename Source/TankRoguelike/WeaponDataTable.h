
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
class TANKROGUELIKE_API AWeaponDataTable : public AActorDataTable
{
	GENERATED_BODY()
};
