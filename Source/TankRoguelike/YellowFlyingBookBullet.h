
#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "YellowFlyingBookBullet.generated.h"

UCLASS()
class TANKROGUELIKE_API AYellowFlyingBookBullet : public ABullet
{
	GENERATED_BODY()

public:

	AYellowFlyingBookBullet();

	virtual void Init(FVector SpawnLocation, FRotator FireRotation, class AUnit* InstigatorData) override;

	virtual void Tick(float DeltaTime) override;

	void SetBulletCenter(class AYellowFlyingBookBulletCenter* YellowFlyingBookBulletCenter);

private:

	class AYellowFlyingBookBulletCenter* BulletCenter;

	float RotatingAmount;
	bool Plag;
};
