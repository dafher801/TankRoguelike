
#include "BlueFlyingBookBullet.h"
#include "BulletDataTable.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABlueFlyingBookBullet::ABlueFlyingBookBullet()
	: ABullet(EUnitTag::BLUEFLYINGBOOK)
{
	Cast<USphereComponent>(ShapeCollision)->SetSphereRadius(20.0f);
	ShapeCollision->BodyInstance.SetCollisionProfileName("EnemyAttack");

	static UFlipbookAsset Bullet = TEXT("/Game/Flipbooks/Bullets/BluePencil");
	BulletFlipbook->SetFlipbook(Bullet.Object);
}

void ABlueFlyingBookBullet::Init(FVector SpawnLocation, FRotator FireRotation, AUnit* InstigatorData)
{
	Super::Init(SpawnLocation, FireRotation, InstigatorData);
}

void ABlueFlyingBookBullet::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);

		SetActorRotation((PlayerActor->GetActorLocation() - GetActorLocation()).Rotation() + BulletData->CollisionRotation);
		Movement->Velocity = (PlayerActor->GetActorLocation() - GetActorLocation()).Rotation().Vector() * Movement->InitialSpeed;
	}
}

void ABlueFlyingBookBullet::BeginPlay()
{
	Super::BeginPlay();

	PlayerActor = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
}
