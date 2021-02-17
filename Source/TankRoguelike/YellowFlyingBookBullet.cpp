
#include "YellowFlyingBookBullet.h"
#include "YellowFlyingBookBulletCenter.h"
#include "BulletDataTable.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AYellowFlyingBookBullet::AYellowFlyingBookBullet()
	: ABullet(EUnitTag::YELLOWFLYINGBOOK)
	, RotatingAmount(1.0f)
{
	Cast<USphereComponent>(ShapeCollision)->SetSphereRadius(20.0f);
	ShapeCollision->BodyInstance.SetCollisionProfileName("EnemyAttack");

	static UFlipbookAsset Bullet = TEXT("/Game/Flipbooks/Bullets/YellowPencil");
	BulletFlipbook->SetFlipbook(Bullet.Object);
}

void AYellowFlyingBookBullet::Init(FVector SpawnLocation, FRotator FireRotation, AUnit* InstigatorData)
{
	Super::Init(SpawnLocation, FireRotation, InstigatorData);

	BulletCenter->GetMovement()->InitialSpeed = BulletData->Status.MoveSpeed;
	BulletCenter->GetMovement()->MaxSpeed = BulletData->Status.MoveSpeed;

	Movement->InitialSpeed = RotatingAmount * 2 * PI * BulletCenter->GetRadius();
	Movement->MaxSpeed = RotatingAmount * 2 * PI * BulletCenter->GetRadius();
}

void AYellowFlyingBookBullet::Tick(float DeltaTime)
{
	if (bActivated)
	{
		AddActorWorldRotation(FRotator(0.0f, DeltaTime * 360.0f, 0.0f));

		Movement->Velocity = (GetActorForwardVector().Rotation() + 
			FRotator(0.0f, 90.0f, 0.0f)).Vector() * Movement->MaxSpeed;

		Movement->Velocity += BulletCenter->GetMovement()->Velocity;

		Super::Tick(DeltaTime);
	}
}

void AYellowFlyingBookBullet::SetBulletCenter(AYellowFlyingBookBulletCenter* YellowFlyingBookBulletCenter)
{
	BulletCenter = YellowFlyingBookBulletCenter;
}
