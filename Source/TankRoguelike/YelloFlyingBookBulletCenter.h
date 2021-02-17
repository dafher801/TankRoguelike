
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YelloFlyingBookBulletCenter.generated.h"

UCLASS()
class TANKROGUELIKE_API AYelloFlyingBookBulletCenter : public AActor
{
	GENERATED_BODY()
	
public:	

	AYelloFlyingBookBulletCenter();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
