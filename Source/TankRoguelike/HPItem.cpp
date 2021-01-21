
#include "HPItem.h"
#include "Tank.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"

AHPItem::AHPItem()
{
	BoxCollision->SetBoxExtent(FVector(14.0f, 10.0f, 15.0f), true);

	static UFlipbookAsset ItemAsset = TEXT("/Game/Flipbooks/Items/HP");
	ItemFlipbook->SetFlipbook(ItemAsset.Object);
}

void AHPItem::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);
	}
}

void AHPItem::OnHit(UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		float BaseHP = Cast<ATank>(OtherActor)->GetBaseStatus().HP;
		float CurrentHP = Cast<ATank>(OtherActor)->GetCurrentStatus().HP;

		Status.HP = BaseHP / 10.0f;

		if (CurrentHP + Status.HP > BaseHP)
			Status.HP = BaseHP - CurrentHP;
		
		Cast<ATank>(OtherActor)->GetItem(this);
		SetActivated(false);
	}
}

void AHPItem::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentHit.AddDynamic(this, &AHPItem::OnHit);
}
