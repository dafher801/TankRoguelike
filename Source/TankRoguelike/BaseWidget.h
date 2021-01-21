
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

UCLASS(Blueprintable)
class TANKROGUELIKE_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
		class ATankRoguelikeGameMode* TankRoguelikeGameMode;
};
