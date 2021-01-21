
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "TankRoguelikeGameInstance.generated.h"

UCLASS()
class TANKROGUELIKE_API UTankRoguelikeGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:

    UTankRoguelikeGameInstance();

    virtual void Init();

public:

    FStreamableManager AssetLoader;
};
