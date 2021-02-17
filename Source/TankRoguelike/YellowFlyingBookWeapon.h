
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

	virtual void ClearBullets() const;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
		TArray<class AYellowFlyingBookBulletCenter*> CenterObjectPool;

	int CurrentBulletCenterNum;
	int MaxBulletCenterNum;
};
