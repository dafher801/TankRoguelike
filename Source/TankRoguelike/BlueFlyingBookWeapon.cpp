
#include "BlueFlyingBookWeapon.h"
#include "BlueFlyingBookBullet.h"
#include "Kismet/GamePlayStatics.h"

UBlueFlyingBookWeapon::UBlueFlyingBookWeapon()
	: UWeaponComponent(EUnitTag::BLUEFLYINGBOOK)
{
}

void UBlueFlyingBookWeapon::Aim()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
		TargetLocation = PlayerPawn->GetActorLocation();

	Super::Aim();
}

void UBlueFlyingBookWeapon::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < WeaponData->MaxBulletNum; i++)
		BulletObjectPool.Add(GetWorld()->SpawnActor<ABlueFlyingBookBullet>(ABlueFlyingBookBullet::StaticClass()));
}