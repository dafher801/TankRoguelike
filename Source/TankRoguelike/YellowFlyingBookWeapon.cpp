
#include "YellowFlyingBookWeapon.h"
#include "YellowFlyingBookBullet.h"
#include "YellowFlyingBookBulletCenter.h"
#include "Kismet/GameplayStatics.h"

UYellowFlyingBookWeapon::UYellowFlyingBookWeapon()
	: UWeaponComponent(EUnitTag::YELLOWFLYINGBOOK)
	, MaxBulletCenterNum(5)
	, CurrentBulletCenterNum(0)
{
}

void UYellowFlyingBookWeapon::InitFire(AUnit* InstigatorData)
{
	if (CurrentBulletCenterNum >= MaxBulletCenterNum)
		CurrentBulletCenterNum = 0;

	for (int i = CurrentBulletCenterNum++; i < MaxBulletCenterNum; i++)
	{
		if (!CenterObjectPool[i]->GetActivated())
		{
			CenterObjectPool[i]->Init(GetComponentLocation(),
				FireRotation + WeaponData->RevisedFireRotation, InstigatorData);

			return;
		}
	}
}

void UYellowFlyingBookWeapon::Aim()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
		TargetLocation = PlayerPawn->GetActorLocation();

	Super::Aim();
}

void UYellowFlyingBookWeapon::ClearBullets() const
{
	for (int i = 0; i < MaxBulletCenterNum; i++)
		CenterObjectPool[i]->ClearBullets();
}

void UYellowFlyingBookWeapon::BeginPlay()
{
	int i;

	Super::BeginPlay();

	for (i = 0; i < MaxBulletCenterNum; i++)
	{
		CenterObjectPool.Add(GetWorld()->SpawnActor
			<AYellowFlyingBookBulletCenter>(AYellowFlyingBookBulletCenter::StaticClass()));
	}
}