
#include "HPItem.h"
#include "BaseTank.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

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

void AHPItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		float BaseHP = Cast<ABaseTank>(OtherActor)->GetBaseStatus().HP;
		float CurrentHP = Cast<ABaseTank>(OtherActor)->GetCurrentStatus().HP;

		Status.HP = BaseHP / 10.0f;

		if (CurrentHP + Status.HP > BaseHP)
			Status.HP = BaseHP - CurrentHP;

		Cast<ABaseTank>(OtherActor)->GetItem(this);
		SetActivated(false);
	}
}

void AHPItem::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AHPItem::OnOverlapBegin);
}
