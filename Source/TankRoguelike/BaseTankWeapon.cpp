
#include "BaseTankWeapon.h"
#include "BaseTankBullet.h"
#include "Kismet/GamePlayStatics.h"
#include "PaperFlipbookComponent.h"

UBaseTankWeapon::UBaseTankWeapon()
	: UWeaponComponent(EUnitTag::TANK)
{
	WeaponFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("WeaponFlipbook"));
	static UFlipbookAsset TankWeaponIdle = TEXT("/Game/Flipbooks/Tanks/TankWeaponIdle");
	WeaponFlipbook->SetRelativeLocation(FVector(0.0f, -1.0f, 0.0f));
	WeaponFlipbook->SetFlipbook(TankWeaponIdle.Object);
	WeaponFlipbook->SetupAttachment(this);
}

void UBaseTankWeapon::Aim()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		DeprojectMousePositionToWorld(TargetLocation, WorldDirection);

	Super::Aim();
}

void UBaseTankWeapon::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < WeaponData->MaxBulletNum; i++)
		BulletObjectPool.Add(GetWorld()->SpawnActor<ABaseTankBullet>(ABaseTankBullet::StaticClass()));
}