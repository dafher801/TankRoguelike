
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Containers/Array.h"
#include "TankRoguelikeGameModeBase.generated.h"

UCLASS(BlueprintType)
class TANKROGUELIKE_API ATankRoguelikeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ATankRoguelikeGameModeBase();

	virtual void Tick(float DeltaTime) override;

	void SpawnEnemy();

	void SpawnItem(FVector SpawnLocation);

	UFUNCTION(BlueprintCallable)
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidget);

	UFUNCTION(BlueprintCallable)
		void StartGame();

	UFUNCTION(BlueprintCallable)
		void InitGame();

	UFUNCTION(BlueprintImplementableEvent)
		void StageClear();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver();

	UFUNCTION(BlueprintCallable)
		class ABaseTank* GetPlayer() const;

	UFUNCTION(BlueprintCallable)
		int GetCurrentStage() const;

	UFUNCTION(BlueprintCallable)
		int GetCountDownTime() const;

	UFUNCTION()
		bool GetPlaying() const;

	bool PayScore(int StatusLevel);

protected:

	virtual void BeginPlay() override;

private:

	void CountDown();

protected:

	UPROPERTY()
		FTimerHandle SpawnEnemyTimer;

	UPROPERTY()
		FTimerHandle CountDownTimer;

	UPROPERTY()
		class UUserWidget* CurrentWidget;

	UPROPERTY(BlueprintReadWrite)
		class ABaseTank* Player;

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
	int CurrentStage;

	int CountDownTime;

	int BaseUpgradePay;
	int AdditionalPay;
};
