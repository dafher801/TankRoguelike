
#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "BlueFlyingBook.generated.h"

UCLASS()
class TANKROGUELIKE_API ABlueFlyingBook : public AEnemy
{
	GENERATED_BODY()

public:

	ABlueFlyingBook();

	virtual void Init() override;

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	// �Ʒ��� �� �Լ��� ������ Tick�Լ� ������ ����Ǿ�� �մϴ�.
	virtual void Move() override;
	virtual void Fire(float DeltaTime) override;
};
