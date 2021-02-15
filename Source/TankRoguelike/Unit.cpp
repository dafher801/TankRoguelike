
#include "Unit.h"
#include "UnitDataTable.h"
#include "WeaponComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "UObject/ConstructorHelpers.h"

AUnit::AUnit(const EUnitTag& UnitTag)
	: UnitTag(UnitTag)
	, KindOfStatus(6)
{
	PrimaryActorTick.bCanEverTick = true;

	static UDataTableAsset UnitDataTable = TEXT("/Game/DataTables/UnitDataTable");

	UnitData = UnitDataTable.Object->FindRow<FUnitData>(
		UnitDataTable.Object->GetRowNames()[static_cast<int>(UnitTag)], FString(""));

	BaseStatus = UnitData->Status;
	Score = UnitData->Score;

	switch (UnitData->ActorCollisionShape)
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

	ShapeCollision->SetWorldScale3D(UnitData->Scale);
	ShapeCollision->SetConstraintMode(EDOFMode::Type::XYPlane);
	RootComponent = ShapeCollision;

	BodyFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BodyFlipbook"));
	BodyFlipbook->AddLocalRotation(UnitData->FlipbookRotation);
	BodyFlipbook->SetupAttachment(RootComponent);

	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	Direction->AddLocalRotation(UnitData->DirectionRotation);
	Direction->SetupAttachment(ShapeCollision);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	SetActivated(false);
}

void AUnit::Init()
{
	SetActivated(true);

	CurrentStatus = BaseStatus;

	bIsEnableAttack = true;
	TimeElapsedSinceAttack = 0.0f;

	SetActorRotation(UnitData->CollisionRotation);

	if (WeaponComponent)
		WeaponComponent->Init();
}

void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AUnit::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount -= CurrentStatus.DEF;

	if (DamageAmount > 0)
		CurrentStatus.HP -= DamageAmount;
	else
		DamageAmount = 0;

	if (CurrentStatus.HP <= 0.0f)
	{
		SetActivated(false);
		DetachFromControllerPendingDestroy();
	}

	return DamageAmount;
}

void AUnit::OnHit(UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit)
{
}

bool AUnit::GetActivated() const
{
	return bActivated;
}

void AUnit::SetActivated(bool Activated)
{
	bActivated = Activated;
	
	if (Movement)
		Movement->SetActive(bActivated);

	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

FStatus AUnit::GetBaseStatus() const
{
	return BaseStatus;
}

FStatus AUnit::GetCurrentStatus() const
{
	return CurrentStatus;
}

int AUnit::GetScore() const
{
	return Score;
}

UWeaponComponent* AUnit::GetWeaponComponent() const
{
	return WeaponComponent;
}

void AUnit::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(UnitData->CollisionRotation);
}

void AUnit::Move()
{
	SetActorRotation(BodyRotation + UnitData->CollisionRotation);
	AddMovementInput(MoveVector);
}

void AUnit::Fire(float DeltaTime)
{
	if (1.0f / CurrentStatus.AttackSpeed - (TimeElapsedSinceAttack += DeltaTime) <= 0)
	{
		WeaponComponent->InitFire(this);
		TimeElapsedSinceAttack = 0.0f;
	}
}
