
#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Containers/Array.h"
#include "TankRoguelikeGameMode.generated.h"

UCLASS(BlueprintType)
class TANKROGUELIKE_API ATankRoguelikeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ATankRoguelikeGameMode();

	virtual void Tick(float DeltaTime) override;

	void SpawnItem(FVector SpawnLocation);

	UFUNCTION(BlueprintCallable)
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidget);

	UFUNCTION(BlueprintCallable)
		void StartGame();

	UFUNCTION(BlueprintCallable)
		void ClearGame();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver();

	UFUNCTION(BlueprintCallable)
		class ATank* GetPlayer() const;

protected:

	virtual void BeginPlay() override;

private:

	void SpawnEnemy();

protected:

	UPROPERTY()
		FTimerHandle TimerHandle;

	UPROPERTY()
		class UUserWidget* CurrentWidget;

	UPROPERTY(BlueprintReadWrite)
		class ATank* Player;

	UPROPERTY(BlueprintReadWrite)
		int TotalScore;

	UPROPERTY(BlueprintReadWrite)
		bool bPlaying;

	TArray<TArray<class AEnemy*>> EnemyObjectPool;
	TArray<class AItem*> ItemObjectPool;

	float NecessaryTimeForSpawn;
	float CurrentTimeForSpawn;

	int KindOfEnemyNum;
	int MaxEnemyNum;
	int CurrentEnemyNum;

	int CurrentItemNum;
};
