
#include "GreenFlyingBookBullet.h"
#include "BulletDataTable.h"
#include "PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGreenFlyingBookBullet::AGreenFlyingBookBullet()
	: ABullet(EUnitTag::GREENFLYINGBOOK)
{
	Cast<USphereComponent>(ShapeCollision)->SetSphereRadius(20.0f);
	ShapeCollision->BodyInstance.SetCollisionProfileName("EnemyAttack");

	static UFlipbookAsset Bullet = TEXT("/Game/Flipbooks/Bullets/GreenPencil");
	BulletFlipbook->SetFlipbook(Bullet.Object);
}

void AGreenFlyingBookBullet::Init(FVector SpawnLocation, FRotator FireRotation, AUnit* UnitInstigator)
{
	Super::Init(SpawnLocation, FireRotation, UnitInstigator);
}