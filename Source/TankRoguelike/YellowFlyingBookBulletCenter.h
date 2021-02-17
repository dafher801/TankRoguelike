
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "YellowFlyingBookBulletCenter.generated.h"

UCLASS()
class TANKROGUELIKE_API AYellowFlyingBookBulletCenter : public AActor
{
	GENERATED_BODY()

public:

	AYellowFlyingBookBulletCenter();

	virtual void Init(FVector SpawnLocation, FRotator FireRotation, class AUnit* InstigatorData);

	virtual void Tick(float DeltaTime) override;

	bool GetActivated() const;
	void SetActivated(bool Activated);

	float GetRadius() const;

	class UProjectileMovementComponent* GetMovement() const;

	void ClearBullets() const;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
		class USphereComponent* Collision;

	UPROPERTY()
		class UProjectileMovementComponent* Movement;

	UPROPERTY()
		TArray<class AYellowFlyingBookBullet*> BulletObjectPool;

	bool bActivated;

	float Radius;
	int MaxBulletNum;
};
