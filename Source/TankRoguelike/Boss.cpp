
#include "Boss.h"
#include "BossWeapon.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

ABoss::ABoss()
	//: AEnemy(EUnitTag::BOSS)
{
	/*Cast<UBoxComponent>(ShapeCollision)->SetBoxExtent(FVector(40.0f, 40.0f, 40.0f), true);
	ShapeCollision->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
	SetActorLocation(FVector(750.0f, 0.0f, 0.0f));
	
	WeaponComponent = CreateDefaultSubobject<UBossWeapon>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(ShapeCollision);

	static UFlipbookAsset BossIdle = TEXT("/Game/Flipbooks/Monsters/Boss");
	BodyFlipbook->SetFlipbook(BossIdle.Object);*/
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
}

void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Super::Fire(DeltaTime);
}