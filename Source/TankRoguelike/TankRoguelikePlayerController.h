
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankRoguelikePlayerController.generated.h"

UCLASS()
class TANKROGUELIKE_API ATankRoguelikePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATankRoguelikePlayerController();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
};
