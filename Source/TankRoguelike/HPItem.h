
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
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

protected:

	virtual void BeginPlay() override;
};
