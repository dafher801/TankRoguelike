
#include "YellowFlyingBookBulletCenter.h"
#include "YellowFlyingBookBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AYellowFlyingBookBulletCenter::AYellowFlyingBookBulletCenter()
	: bActivated(false)
	, Radius(200.0f)
	, MaxBulletNum(4)
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Collision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	Collision->SetConstraintMode(EDOFMode::Type::XYPlane);
	RootComponent = Collision;

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->ProjectileGravityScale = 0.0f;

	SetActivated(false);
}

void AYellowFlyingBookBulletCenter::Init(FVector SpawnLocation, FRotator FireRotation, AUnit* InstigatorData)
{
	SetActorLocation(SpawnLocation);

	SetActivated(true);

	for (int i = 0; i < MaxBulletNum; i++)
		BulletObjectPool[i]->SetBulletCenter(this);

	BulletObjectPool[0]->Init(SpawnLocation + 
		FVector(Radius, 0.0f, 0.0f), FRotator(0.0f, 90.0f, 0.0f), InstigatorData);

	BulletObjectPool[1]->Init(SpawnLocation +
		FVector(0.0f, Radius, 0.0f), FRotator(0.0f, 180.0f, 0.0f), InstigatorData);
	
	BulletObjectPool[2]->Init(SpawnLocation + 
		FVector(-1 * Radius, 0.0f, 0.0f), FRotator(0.0f, -90.0f, 0.0f), InstigatorData);
	
	BulletObjectPool[3]->Init(SpawnLocation +
		FVector(0.0f, -1 * Radius, 0.0f), FRotator(0.0f, 0.0f, 0.0f), InstigatorData);

	Movement->Velocity = FireRotation.Vector() * Movement->InitialSpeed;
}

void AYellowFlyingBookBulletCenter::Tick(float DeltaTime)
{
	if (bActivated)
	{
		int i;

		for (i = 0; i < MaxBulletNum; i++)
		{
			if (BulletObjectPool[i]->GetActivated())
				break;
		}

		if (i >= MaxBulletNum)
			SetActivated(false);

		AActor::Tick(DeltaTime);
	}
}

bool AYellowFlyingBookBulletCenter::GetActivated() const
{
	return bActivated;
}

void AYellowFlyingBookBulletCenter::SetActivated(bool Activated)
{
	bActivated = Activated;
	Movement->SetActive(bActivated);
	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
}

float AYellowFlyingBookBulletCenter::GetRadius() const
{
	return Radius;
}

UProjectileMovementComponent* AYellowFlyingBookBulletCenter::GetMovement() const
{
	return Movement;
}

void AYellowFlyingBookBulletCenter::ClearBullets() const
{
	for (int i = 0; BulletObjectPool.Num() && i < MaxBulletNum; i++)
		BulletObjectPool[i]->SetActivated(false);
}

void AYellowFlyingBookBulletCenter::BeginPlay()
{
	AActor::BeginPlay();

	for (int i = 0; i < MaxBulletNum; i++)
	{
		BulletObjectPool.Add(GetWorld()->
			SpawnActor<AYellowFlyingBookBullet>(AYellowFlyingBookBullet::StaticClass()));
	}
}