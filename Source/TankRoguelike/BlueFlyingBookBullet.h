
#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "BlueFlyingBookBullet.generated.h"

UCLASS()
class TANKROGUELIKE_API ABlueFlyingBookBullet : public ABullet
{
	GENERATED_BODY()

public:

	ABlueFlyingBookBullet();

	virtual void Init(FVector SpawnLocation, FRotator FireRotation, class AUnit* UnitInstigator) override;

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	AActor* PlayerActor;

	float MaxTheta;
	float DistanceForRotate;
	float RestForRotate;
};
