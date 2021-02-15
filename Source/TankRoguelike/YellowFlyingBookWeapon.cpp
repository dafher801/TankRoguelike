
#include "YellowFlyingBookWeapon.h"
#include "YellowFlyingBookBullet.h"
#include "Kismet/GameplayStatics.h"

UYellowFlyingBookWeapon::UYellowFlyingBookWeapon()
	: UWeaponComponent(EUnitTag::YELLOWFLYINGBOOK)
{
}

void UYellowFlyingBookWeapon::InitFire(AUnit* InstigatorData)
{
	Super::InitFire(InstigatorData);
}


void UYellowFlyingBookWeapon::Aim()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
		TargetLocation = PlayerPawn->GetActorLocation();

	Super::Aim();
}

void UYellowFlyingBookWeapon::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < WeaponData->MaxBulletNum; i++)
		BulletObjectPool.Add(GetWorld()->SpawnActor<AYellowFlyingBookBullet>(AYellowFlyingBookBullet::StaticClass()));
}