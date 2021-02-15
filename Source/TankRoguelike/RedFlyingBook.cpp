
#include "RedFlyingBook.h"
#include "RedFlyingBookWeapon.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Math/Color.h"

ARedFlyingBook::ARedFlyingBook()
	: AEnemy(EUnitTag::REDFLYINGBOOK)
{
	Cast<UBoxComponent>(ShapeCollision)->SetBoxExtent(FVector(120.0f, 75.0f, 32.0f), true);

	WeaponComponent = CreateDefaultSubobject<URedFlyingBookWeapon>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(ShapeCollision);

	static UFlipbookAsset FlyingBookIdle = TEXT("/Game/Flipbooks/Monsters/NormalFlyingBook");
	BodyFlipbook->SetFlipbook(FlyingBookIdle.Object);
	BodyFlipbook->SetSpriteColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
}

void ARedFlyingBook::Init()
{
	Super::Init();
}

void ARedFlyingBook::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);

		Move();

		if (WeaponComponent)
			WeaponComponent->Aim();

		Fire(DeltaTime);
	}
}

void ARedFlyingBook::BeginPlay()
{
	Super::BeginPlay();
}

void ARedFlyingBook::Move()
{
	MoveVector = FVector(PlayerLocation.X - GetActorLocation().X, PlayerLocation.Y - GetActorLocation().Y, 0.0f);

	if (MoveVector.Y < 0)
		BodyRotation = FRotator(0.0f, 0.0f, 0.0f);
	else
		BodyRotation = FRotator(180.0f, 0.0f, 0.0f);

	Super::Move();
}

void ARedFlyingBook::Fire(float DeltaTime)
{
	Super::Fire(DeltaTime);
}
