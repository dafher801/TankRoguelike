
#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "YellowFlyingBookWeapon.generated.h"

UCLASS()
class TANKROGUELIKE_API UYellowFlyingBookWeapon : public UWeaponComponent
{
	GENERATED_BODY()

public:

	UYellowFlyingBookWeapon();

	virtual void InitFire(class AUnit* InstigatorData) override;

	virtual void Aim() override;

protected:

	virtual void BeginPlay() override;
};
