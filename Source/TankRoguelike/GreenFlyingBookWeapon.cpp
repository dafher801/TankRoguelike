
#include "GreenFlyingBookWeapon.h"
#include "GreenFlyingBookBullet.h"
#include "Kismet/GamePlayStatics.h"

UGreenFlyingBookWeapon::UGreenFlyingBookWeapon()
	: UWeaponComponent(EUnitTag::GREENFLYINGBOOK)
{
}

void UGreenFlyingBookWeapon::Aim()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
		TargetLocation = PlayerPawn->GetActorLocation();

	Super::Aim();
}

void UGreenFlyingBookWeapon::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < WeaponData->MaxBulletNum; i++)
		BulletObjectPool.Add(GetWorld()->SpawnActor<AGreenFlyingBookBullet>(AGreenFlyingBookBullet::StaticClass()));
}