
#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "BossWeapon.generated.h"

UCLASS()
class TANKROGUELIKE_API UBossWeapon : public UWeaponComponent
{
	GENERATED_BODY()
	
public:

	UBossWeapon();

	virtual void InitFire(class AUnit* InstigatorData) override;

	virtual void Aim() override;

	FVector GetBulletStartLocation();

	class UEquation* GetEquation() const;

protected:

	virtual void BeginPlay() override;

private:

	class UEquation* Equation;
};
