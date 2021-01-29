
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletDataTable.h"
#include "Bullet.generated.h"

UCLASS()
class TANKROGUELIKE_API ABullet : public AActor
{
	GENERATED_BODY()

public:

	ABullet() {}

	ABullet(const EUnitTag& UnitTag);

	virtual void Init(FVector SpawnLocation, FRotator FireRotation, class AUnit* InstigatorData);

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnHit(class UPrimitiveComponent* OtherComp, class AActor* OtherActor, class UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit);

	bool GetActivated() const;
	void SetActivated(bool Activated);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Collision")
		class UShapeComponent* ShapeCollision;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Visual")
		class UPaperFlipbookComponent* BulletFlipbook;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Helper")
		class UArrowComponent* Direction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement")
		class UProjectileMovementComponent* Movement;

	struct FBulletData* BulletData;

	const FVector BulletScale;

	float MaxMovementDistance;
	float CurrentMovementDistance;

	int Damage;

	bool bActivated;
};
