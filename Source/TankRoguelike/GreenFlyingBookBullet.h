
#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "GreenFlyingBookBullet.generated.h"

UCLASS()
class TANKROGUELIKE_API AGreenFlyingBookBullet : public ABullet
{
	GENERATED_BODY()

public:

	AGreenFlyingBookBullet();

	virtual void Init(FVector SpawnLocation, FRotator FireRotation, class AUnit* InstigatorData) override;
};
