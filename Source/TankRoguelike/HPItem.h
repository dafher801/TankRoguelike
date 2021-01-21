
#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HPItem.generated.h"

UCLASS()
class TANKROGUELIKE_API AHPItem : public AItem
{
	GENERATED_BODY()
	
public:

	AHPItem();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnHit(class UPrimitiveComponent* OtherComp, class AActor* OtherActor, class UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& Hit);


protected:

	virtual void BeginPlay() override;
};
