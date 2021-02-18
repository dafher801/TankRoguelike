
#include "TankRoguelikeGameModeBase.h"
#include "BaseTank.h"
#include "GreenFlyingBook.h"
#include "RedFlyingBook.h"
#include "BlueFlyingBook.h"
#include "YellowFlyingBook.h"
#include "WeaponComponent.h"
#include "UnitDataTable.h"
#include "HPItem.h"
#include "TankRoguelikePlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include <random>
#include <ctime>

ATankRoguelikeGameModeBase::ATankRoguelikeGameModeBase()
	: TotalScore(0)
	, bPlaying(false)
	, NecessaryTimeForSpawn(2000.0f)
	, CurrentTimeForSpawn(0.0f)
	, KindOfEnemyNum(4)
	, MaxEnemyNum(10)
	, CurrentEnemyNum(0)
	, CurrentItemNum(0)
	, CurrentStage(0)
	, CountDownTime(0)
	, BaseUpgradePay(100)
	, AdditionalPay(50)
{
	srand((int)time(NULL));

	static UDataTableAsset UnitDataTableFile = TEXT("/Game/DataTables/UnitDataTable");

	for (int i = 0; i < KindOfEnemyNum; i++)
		EnemyObjectPool.Add(TArray<AEnemy*>());

	PlayerControllerClass = ATankRoguelikePlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}

void ATankRoguelikeGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATankRoguelikeGameModeBase::SpawnEnemy()
{
	int Index = rand() % KindOfEnemyNum;
	FVector SpawnLocation;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!PlayerPawn)
		return;

	do
	{
		SpawnLocation = FVector(FRandomStream(rand()).
			FRandRange(-900, 900), FRandomStream(rand()).FRandRange(-900, 900), 0.0f);
	} while (FVector::Distance(SpawnLocation, PlayerPawn->
		GetActorLocation()) < Player->GetCurrentStatus().Range);

	for (int i = CurrentEnemyNum++; i < MaxEnemyNum; i++)
	{
		if (!EnemyObjectPool[Index][i]->GetActivated())
		{
			EnemyObjectPool[Index][i]->Init();
			EnemyObjectPool[Index][i]->SetActorLocation(SpawnLocation);
			return;
		}
	}

	if (CurrentEnemyNum >= MaxEnemyNum)
		CurrentEnemyNum = 0;
}

void ATankRoguelikeGameModeBase::SpawnItem(FVector SpawnLocation)
{
	if (rand() % 2)
		return;

	if (CurrentItemNum >= 10)
		CurrentItemNum = 0;

	for (int i = CurrentItemNum++; i < 10; i++)
	{
		if (!ItemObjectPool[i]->GetActivated())
		{
			ItemObjectPool[i]->Init();
			ItemObjectPool[i]->SetActorLocation(SpawnLocation);
			return;
		}
	}
}

void ATankRoguelikeGameModeBase::ChangeWidget(TSubclassOf<UUserWidget> NewWidget)
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidget)
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidget);

		if (CurrentWidget)
			CurrentWidget->AddToViewport();
	}
}

void ATankRoguelikeGameModeBase::StartGame()
{
	Player->Init();
	Player->AddScore(TotalScore);

	bPlaying = true;
	++CurrentStage;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetPause(false);
	GetWorldTimerManager().SetTimer(CountDownTimer, this, &ATankRoguelikeGameModeBase::CountDown, 1.0f, true);
	GetWorldTimerManager().SetTimer(SpawnEnemyTimer, this, &ATankRoguelikeGameModeBase::SpawnEnemy, 2.0f, true);
}

void ATankRoguelikeGameModeBase::InitGame()
{
	int i, j;

	for (i = 0; i < KindOfEnemyNum; i++)
	{
		for (j = 0; j < MaxEnemyNum; j++)
		{
			EnemyObjectPool[i][j]->SetActivated(false);
			EnemyObjectPool[i][j]->GetWeaponComponent()->ClearBullets();
			EnemyObjectPool[i][j]->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
		}
	}

	for (i = 0; i < MaxEnemyNum; i++)
	{
		if (ItemObjectPool[i]->GetActivated())
		{
			ItemObjectPool[i]->SetActivated(false);
			ItemObjectPool[i]->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
		}
	}

	if (!bPlaying)
	{
		TotalScore = 0;
		CurrentStage = 0;

		Player->InitLevel();
		Player->GetWeaponComponent()->InitSpeedLevel();
	}
	
	CountDownTime = 100;

	Player->SetActivated(false);
	Player->GetWeaponComponent()->ClearBullets();
	Player->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
}

ABaseTank* ATankRoguelikeGameModeBase::GetPlayer() const
{
	return Player;
}

int ATankRoguelikeGameModeBase::GetCurrentStage() const
{
	return CurrentStage;
}

int ATankRoguelikeGameModeBase::GetCountDownTime() const
{
	return CountDownTime;
}

bool ATankRoguelikeGameModeBase::GetPlaying() const
{
	return bPlaying;
}

bool ATankRoguelikeGameModeBase::PayScore(int StatusLevel)
{
	if (TotalScore < (BaseUpgradePay + StatusLevel * AdditionalPay))
		return false;

	TotalScore -= (BaseUpgradePay + StatusLevel * AdditionalPay);
	return true;
}

void ATankRoguelikeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ABaseTank>(GetWorld()->SpawnActor<ABaseTank>(ABaseTank::StaticClass()));

	for (int i = 0; i < MaxEnemyNum; i++)
	{
		EnemyObjectPool[static_cast<int>(EUnitTag::GREENFLYINGBOOK) - 1].
			Add(Cast<AGreenFlyingBook>(GetWorld()->SpawnActor(AGreenFlyingBook::StaticClass())));

		EnemyObjectPool[static_cast<int>(EUnitTag::REDFLYINGBOOK) - 1].
			Add(Cast<ARedFlyingBook>(GetWorld()->SpawnActor(ARedFlyingBook::StaticClass())));

		EnemyObjectPool[static_cast<int>(EUnitTag::BLUEFLYINGBOOK) - 1].
			Add(Cast<ABlueFlyingBook>(GetWorld()->SpawnActor(ABlueFlyingBook::StaticClass())));

		EnemyObjectPool[static_cast<int>(EUnitTag::YELLOWFLYINGBOOK) - 1].
			Add(Cast<AYellowFlyingBook>(GetWorld()->SpawnActor(AYellowFlyingBook::StaticClass())));

		ItemObjectPool.Add(Cast<AHPItem>(GetWorld()->SpawnActor(AHPItem::StaticClass())));
	}

	InitGame();
}

void ATankRoguelikeGameModeBase::CountDown()
{
	--CountDownTime;

	if (CountDownTime <= 0)
		StageClear();
}
