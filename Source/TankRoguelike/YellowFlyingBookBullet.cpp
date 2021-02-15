
#include "YellowFlyingBookBullet.h"
#include "BulletDataTable.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AYellowFlyingBookBullet::AYellowFlyingBookBullet()
	: ABullet(EUnitTag::YELLOWFLYINGBOOK)
{
	Cast<USphereComponent>(ShapeCollision)->SetSphereRadius(20.0f);
	ShapeCollision->BodyInstance.SetCollisionProfileName("EnemyAttack");

	static UFlipbookAsset Bullet = TEXT("/Game/Flipbooks/Bullets/YellowPencil");
	BulletFlipbook->SetFlipbook(Bullet.Object);
}

void AYellowFlyingBookBullet::Init(FVector SpawnLocation, FRotator FireRotation, AUnit* InstigatorData)
{
	Super::Init(SpawnLocation, FireRotation, InstigatorData);
}

void AYellowFlyingBookBullet::Tick(float DeltaTime)
{
	if (bActivated)
	{
		float cx, cy;
		Super::Tick(DeltaTime);
	}
}