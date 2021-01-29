
#include "WeaponComponent.h"
#include "Unit.h"
#include "Bullet.h"
#include "WeaponDataTable.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"

// 평소대로면 WeaponFlipbook의 생성과 기본적인 세팅을 여기서 해야하지만
// 무기를 가지고 않는 유닛이 존재해서 WeaponFlipbook을 반드시 생성시킬 필요는
// 없기 때문에 WeaponFlipbook의 생성과 세팅은 자식 클래스에서 수행합니다.

UWeaponComponent::UWeaponComponent(const EUnitTag& UnitTag)
	: WeaponFlipbook(nullptr)
	, BulletNum(0)
{
	static UDataTableAsset WeaponDataTable = TEXT("/Game/DataTables/WeaponDataTable");
	WeaponData = WeaponDataTable.Object->FindRow<FWeaponData>(
		WeaponDataTable.Object->GetRowNames()[static_cast<int>(UnitTag)], FString(""));
}

void UWeaponComponent::Init()
{
	BulletNum = 0;
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

void UWeaponComponent::SetActivated(bool Activated)
{
	for (int i = 0; i < WeaponData->MaxBulletNum; i++)
	{
		BulletObjectPool[i]->SetActivated(Activated);
	}
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}