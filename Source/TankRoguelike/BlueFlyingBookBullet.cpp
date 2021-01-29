
#include "BlueFlyingBookBullet.h"
#include "BulletDataTable.h"
#include "Unit.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABlueFlyingBookBullet::ABlueFlyingBookBullet()
	: ABullet(EUnitTag::BLUEFLYINGBOOK)
	, MaxTheta(10.0f)
	, DistanceForRotate(100.0f)
	, RestForRotate(DistanceForRotate)
{
	Cast<USphereComponent>(ShapeCollision)->SetSphereRadius(20.0f);
	ShapeCollision->BodyInstance.SetCollisionProfileName("EnemyAttack");

	static UFlipbookAsset Bullet = TEXT("/Game/Flipbooks/Bullets/BluePencil");
	BulletFlipbook->SetFlipbook(Bullet.Object);
}

void ABlueFlyingBookBullet::Init(FVector SpawnLocation, FRotator FireRotation, AUnit* UnitInstigator)
{
	Super::Init(SpawnLocation, FireRotation, UnitInstigator);
}

void ABlueFlyingBookBullet::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);

		SetActorRotation((PlayerActor->GetActorLocation() - GetActorLocation()).Rotation() + BulletData->CollisionRotation);
		Movement->Velocity = (PlayerActor->GetActorLocation() - GetActorLocation()).Rotation().Vector() * Movement->MaxSpeed;
	}
}

void ABlueFlyingBookBullet::BeginPlay()
{
	Super::BeginPlay();

	PlayerActor = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
}
