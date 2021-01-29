
#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "BaseTankWeapon.generated.h"

UCLASS()
class TANKROGUELIKE_API UBaseTankWeapon : public UWeaponComponent
{
	GENERATED_BODY()

public:

	UBaseTankWeapon();

	virtual void Aim();

protected:

	virtual void BeginPlay() override;

protected:

	FVector WorldDirection;
};
