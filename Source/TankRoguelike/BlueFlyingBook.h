
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

	// 아래의 두 함수는 무조건 Tick함수 내에서 실행되어야 합니다.
	virtual void Move() override;
	virtual void Fire(float DeltaTime) override;
};
