
#include "RedFlyingBookBullet.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ARedFlyingBookBullet::ARedFlyingBookBullet()
	: ABullet(EUnitTag::REDFLYINGBOOK)
{
	Cast<USphereComponent>(ShapeCollision)->SetSphereRadius(20.0f);
	ShapeCollision->BodyInstance.SetCollisionProfileName("EnemyAttack");

	static UFlipbookAsset Bullet = TEXT("/Game/Flipbooks/Bullets/RedPencil");
	BulletFlipbook->SetFlipbook(Bullet.Object);
}

void ARedFlyingBookBullet::Init(FVector SpawnLocation, FRotator FireRotation, AUnit* InstigatorData)
{
	Super::Init(SpawnLocation, FireRotation, InstigatorData);

	Movement->Velocity = FireRotation.Vector() * Movement->InitialSpeed;
}