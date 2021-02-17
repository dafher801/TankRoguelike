
#include "WeaponComponent.h"
#include "Unit.h"
#include "Bullet.h"
#include "WeaponDataTable.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"

// ��Ҵ�θ� WeaponFlipbook�� ������ �⺻���� ������ ���⼭ �ؾ�������
// ���⸦ ������ �ʴ� ������ �����ؼ� WeaponFlipbook�� �ݵ�� ������ų �ʿ��
// ���� ������ WeaponFlipbook�� ������ ������ �ڽ� Ŭ�������� �����մϴ�.

UWeaponComponent::UWeaponComponent(const EUnitTag& UnitTag)
	: WeaponFlipbook(nullptr)
	, BulletNum(0)
	, bActivated(false)
{
	static UDataTableAsset WeaponDataTable = TEXT("/Game/DataTables/WeaponDataTable");
	WeaponData = WeaponDataTable.Object->FindRow<FWeaponData>(
		WeaponDataTable.Object->GetRowNames()[static_cast<int>(UnitTag)], FString(""));
}

void UWeaponComponent::Init()
{
	BulletNum = 0;

	SetActivated(true);
}

void UWeaponComponent::InitFire(AUnit* InstigatorData)
{
	if (BulletNum >= WeaponData->MaxBulletNum)
		BulletNum = 0;

	for (int i = BulletNum++; i < WeaponData->MaxBulletNum; i++)
	{
		if (!BulletObjectPool[i]->GetActivated())
		{
			BulletObjectPool[i]->Init(GetComponentLocation(),
				FireRotation + WeaponData->RevisedFireRotation, InstigatorData);

			return;
		}
	}
}

void UWeaponComponent::Aim()
{
	FVector2D UnitScreen;
	FVector2D TargetScreen;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		ProjectWorldLocationToScreen(GetComponentLocation(), UnitScreen, true);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		ProjectWorldLocationToScreen(TargetLocation, TargetScreen, true);

	FireRotation = FVector(TargetScreen.X - UnitScreen.X, TargetScreen.Y - UnitScreen.Y, 0.0f).Rotation();

	if (WeaponFlipbook)
		WeaponFlipbook->SetWorldRotation(FireRotation + WeaponData->FlipbookRotation);
}

bool UWeaponComponent::GetActivated() const
{
	return bActivated;
}

void UWeaponComponent::SetActivated(bool Activated)
{
	bActivated = Activated;
}

void UWeaponComponent::ClearBullets() const
{
	for (int i = 0; i < WeaponData->MaxBulletNum; i++)
		BulletObjectPool[i]->SetActivated(false);
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}