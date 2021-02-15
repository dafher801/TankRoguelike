
#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "BaseTankBullet.generated.h"

UCLASS()
class TANKROGUELIKE_API ABaseTankBullet : public ABullet
{
	GENERATED_BODY()

public:

	ABaseTankBullet();

	virtual void Init(FVector SpawnLocation, FRotator FireRotation, class AUnit* InstigatorData);

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
};
