
#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "YellowFlyingBook.generated.h"

UCLASS()
class TANKROGUELIKE_API AYellowFlyingBook : public AEnemy
{
	GENERATED_BODY()

public:

	AYellowFlyingBook();

	virtual void Init() override;

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	// �Ʒ��� �� �Լ��� ������ Tick�Լ� ������ ����Ǿ�� �մϴ�.
	virtual void Move() override;
	virtual void Fire(float DeltaTime) override;
};
