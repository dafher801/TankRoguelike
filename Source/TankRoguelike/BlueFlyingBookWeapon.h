
#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "BlueFlyingBookWeapon.generated.h"

UCLASS()
class TANKROGUELIKE_API UBlueFlyingBookWeapon : public UWeaponComponent
{
	GENERATED_BODY()

public:

	UBlueFlyingBookWeapon();

	virtual void Aim() override;

protected:

	virtual void BeginPlay() override;
};
