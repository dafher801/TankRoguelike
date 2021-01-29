
#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "RedFlyingBook.generated.h"

UCLASS()
class TANKROGUELIKE_API ARedFlyingBook : public AEnemy
{
	GENERATED_BODY()

public:

	ARedFlyingBook();

	virtual void Init() override;

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	// �Ʒ��� �� �Լ��� ������ Tick�Լ� ������ ����Ǿ�� �մϴ�.
	virtual void Move() override;
	virtual void Fire(float DeltaTime) override;
};
