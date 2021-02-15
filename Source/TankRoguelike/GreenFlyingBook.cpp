
#include "GreenFlyingBook.h"
#include "GreenFlyingBookWeapon.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Math/Color.h"

AGreenFlyingBook::AGreenFlyingBook()
	: AEnemy(EUnitTag::GREENFLYINGBOOK)
{
	Cast<UBoxComponent>(ShapeCollision)->SetBoxExtent(FVector(120.0f, 75.0f, 32.0f), true);

	WeaponComponent = CreateDefaultSubobject<UGreenFlyingBookWeapon>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(ShapeCollision);

	static UFlipbookAsset FlyingBookIdle = TEXT("/Game/Flipbooks/Monsters/NormalFlyingBook");
	BodyFlipbook->SetFlipbook(FlyingBookIdle.Object);
	BodyFlipbook->SetSpriteColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
}

void AGreenFlyingBook::Init()
{
	Super::Init();
}

void AGreenFlyingBook::Tick(float DeltaTime)
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

void AGreenFlyingBook::BeginPlay()
{
	Super::BeginPlay();
}

void AGreenFlyingBook::Move()
{
	MoveVector = FVector(PlayerLocation.X - GetActorLocation().X, PlayerLocation.Y - GetActorLocation().Y, 0.0f);

	if (MoveVector.Y < 0)
		BodyRotation = FRotator(0.0f, 0.0f, 0.0f);
	else
		BodyRotation = FRotator(180.0f, 0.0f, 0.0f);

	Super::Move();
}

void AGreenFlyingBook::Fire(float DeltaTime)
{
	Super::Fire(DeltaTime);
}
