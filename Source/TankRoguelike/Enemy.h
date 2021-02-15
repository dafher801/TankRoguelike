
#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "Enemy.generated.h"

UCLASS()
class TANKROGUELIKE_API AEnemy : public AUnit
{
	GENERATED_BODY()

public:

	AEnemy() {}

	AEnemy(const EUnitTag& UnitTag);

	virtual void Init() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void LevelUp();

protected:

	virtual void BeginPlay() override;

	// �Ʒ��� �� �Լ��� ������ Tick�Լ� ������ ����Ǿ�� �մϴ�.
	virtual void Move() override;
	virtual void Fire(float DeltaTime) override;

protected:

	class ABaseTank* Player;
	FVector PlayerLocation;
};
