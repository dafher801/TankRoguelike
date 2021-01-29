
#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "GreenFlyingBookWeapon.generated.h"

UCLASS()
class TANKROGUELIKE_API UGreenFlyingBookWeapon : public UWeaponComponent
{
	GENERATED_BODY()

public:

	UGreenFlyingBookWeapon();

	virtual void Aim() override;

protected:

	virtual void BeginPlay() override;
};
