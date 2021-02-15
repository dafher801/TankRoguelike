
#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "RedFlyingBookWeapon.generated.h"

UCLASS()
class TANKROGUELIKE_API URedFlyingBookWeapon : public UWeaponComponent
{
	GENERATED_BODY()

public:

	URedFlyingBookWeapon();

	virtual void InitFire(class AUnit* InstigatorData) override;

	virtual void Aim() override;

protected:

	virtual void BeginPlay() override;
};
