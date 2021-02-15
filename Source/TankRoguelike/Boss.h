
#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Boss.generated.h"

UCLASS()
class TANKROGUELIKE_API ABoss : public AEnemy
{
	GENERATED_BODY()
	
public:

	ABoss();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	/*UPROPERTY()
		class UBossWeapon* BossWeapon;*/

	UPROPERTY()
		FTimerHandle TimerHandle;
};
