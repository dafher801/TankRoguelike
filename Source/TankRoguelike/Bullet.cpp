
#include "Bullet.h"
#include "Unit.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABullet::ABullet(const EUnitTag& UnitTag)
	: MaxMovementDistance(0.0f)
	, CurrentMovementDistance(0.0f)
	, Damage(0.0f)
	, bActivated(false)
{
	PrimaryActorTick.bCanEverTick = true;

	static UDataTableAsset BulletDataTable = TEXT("/Game/DataTables/BulletDataTable");

	BulletData = BulletDataTable.Object->FindRow<FBulletData>(
		BulletDataTable.Object->GetRowNames()[static_cast<int>(UnitTag)], FString(""));

	switch (BulletData->ActorCollisionShape)
	{
	case EActorCollisionShape::BOX:
		ShapeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
		break;

	case EActorCollisionShape::SPHERE:
		ShapeCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
		break;

	case EActorCollisionShape::CAPSULE:
		ShapeCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
		break;

	default:
		break;
	}

	ShapeCollision->SetWorldScale3D(BulletData->Scale);
	ShapeCollision->SetConstraintMode(EDOFMode::Type::XYPlane);
	RootComponent = ShapeCollision;

	BulletFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("BulletFlipbook");
	BulletFlipbook->AddLocalRotation(BulletData->FlipbookRotation);
	BulletFlipbook->SetupAttachment(RootComponent);

	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	Direction->AddLocalRotation(BulletData->DirectionRotation);
	Direction->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->InitialSpeed = BulletData->Status.MoveSpeed;
	Movement->MaxSpeed = BulletData->Status.MoveSpeed;
	Movement->ProjectileGravityScale = 0.0f;
	
	SetActivated(false);
}

void ABullet::Init(FVector SpawnLocation, FRotator FireRotation, AUnit* InstigatorData)
{
	SetActorLocation(SpawnLocation);
	SetActorRotation(FireRotation + BulletData->CollisionRotation);
	SetInstigator(InstigatorData);

	Movement->Velocity = FireRotation.Vector() * Movement->InitialSpeed;

	Damage = InstigatorData->GetCurrentStatus().ATK;
	MaxMovementDistance = InstigatorData->GetCurrentStatus().Range;
	CurrentMovementDistance = 0.0f;
	
	SetActivated(true);
}

void ABullet::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);

		if ((CurrentMovementDistance += (DeltaTime * Movement->MaxSpeed)) > MaxMovementDistance)
			SetActivated(false);
	}
}

void ABullet::OnHit(UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, Damage,
		UGameplayStatics::GetPlayerController(GetWorld(), 0), this, NULL);

	SetActivated(false);
}

bool ABullet::GetActivated() const
{
	return bActivated;
}

void ABullet::SetActivated(bool Activated)
{
	bActivated = Activated;
	Movement->SetActive(bActivated);
	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(BulletData->CollisionRotation);
	ShapeCollision->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}
