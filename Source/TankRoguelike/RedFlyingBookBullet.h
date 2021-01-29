
#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "RedFlyingBookBullet.generated.h"

UCLASS()
class TANKROGUELIKE_API ARedFlyingBookBullet : public ABullet
{
	GENERATED_BODY()

public:

	ARedFlyingBookBullet();

	virtual void Init(FVector SpawnLocation, FRotator FireRotation, class AUnit* UnitInstigator) override;
};
