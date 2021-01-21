
#include "BaseTankBullet.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABaseTankBullet::ABaseTankBullet()
	: ABullet(EUnitTag::TANK)
{
	Cast<USphereComponent>(ShapeCollision)->SetSphereRadius(20.0f);
	ShapeCollision->BodyInstance.SetCollisionProfileName("PlayerAttack");

	static UFlipbookAsset TankBulletIdle = TEXT("/Game/Flipbooks/Bullets/BaseTankBullet");
	BulletFlipbook->SetFlipbook(TankBulletIdle.Object);
}

void ABaseTankBullet::Init(FVector SpawnLocation, FRotator FireRotation, AUnit* UnitInstigator)
{
	Super::Init(SpawnLocation, FireRotation, UnitInstigator);
}

void ABaseTankBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseTankBullet::BeginPlay()
{
	Super::BeginPlay();
}