
#include "Item.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"

AItem::AItem()
	: Status({})
	, bActivated(false)
{
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("Item");

	static UDataTableAsset ItemDataTable = TEXT("/Game/DataTables/ItemDataTable");
	ItemData = ItemDataTable.Object->FindRow<FItemData>(ItemDataTable.Object->GetRowNames()[0], FString(""));

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxCollision->SetWorldScale3D(ItemData->Scale);
	BoxCollision->SetConstraintMode(EDOFMode::Type::XYPlane);
	BoxCollision->BodyInstance.SetCollisionProfileName("Item");
	RootComponent = BoxCollision;

	ItemFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("ItemFlipbook");
	ItemFlipbook->SetupAttachment(RootComponent);

	SetActorRotation(ItemData->CollisionRotation);
	SetActivated(false);
}

void AItem::Init()
{
	SetActivated(true);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FStatus AItem::GetStatus() const
{
	return Status;
}

bool AItem::GetActivated() const
{
	return bActivated;
}

void AItem::SetActivated(bool Activated)
{
	bActivated = Activated;
	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}