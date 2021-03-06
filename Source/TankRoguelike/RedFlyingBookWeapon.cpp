
#include "RedFlyingBookWeapon.h"
#include "RedFlyingBookBullet.h"
#include "Kismet/GameplayStatics.h"

URedFlyingBookWeapon::URedFlyingBookWeapon()
	: UWeaponComponent(EUnitTag::REDFLYINGBOOK)
{
}

void URedFlyingBookWeapon::InitFire(AUnit* InstigatorData)
{
	FireRotation.Yaw -= 30.0f;

	for (int i = 0; i < 5; i++)
	{
		Super::InitFire(InstigatorData);
		FireRotation.Yaw += 15.0f;
	}
}

void URedFlyingBookWeapon::Aim()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
		TargetLocation = PlayerPawn->GetActorLocation();

	Super::Aim();
}

void URedFlyingBookWeapon::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < WeaponData->MaxBulletNum; i++)
		BulletObjectPool.Add(GetWorld()->SpawnActor<ARedFlyingBookBullet>(ARedFlyingBookBullet::StaticClass()));
}