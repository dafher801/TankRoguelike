
#include "BossWeapon.h"
#include "BossBullet.h"
#include "Unit.h"
#include "Equation.h"

UBossWeapon::UBossWeapon()
	//: UWeaponComponent(EUnitTag::BOSS)
{
}

void UBossWeapon::InitFire(AUnit* InstigatorData)
{
	Equation = NewObject<UEquation>();
	Equation->GetRoot();

	/*if (BulletNum >= WeaponData->MaxBulletNum)
		BulletNum = 0;

	for (int i = BulletNum++; i < WeaponData->MaxBulletNum; i++)
	{
		if (!BulletObjectPool[i]->GetActivated())
		{
			BulletObjectPool[i]->Init(FVector(500.0f, -500.0f, 0.0f),
				FireRotation + WeaponData->RevisedFireRotation, InstigatorData);

			return;
		}
	}*/
}

void UBossWeapon::Aim()
{
	//Equation->GetDifferntiation(20.0f);
}

FVector UBossWeapon::GetBulletStartLocation()
{
	return FVector(0.0f, 0.0f, 0.0f);
}

UEquation* UBossWeapon::GetEquation() const
{
	return Equation;
}

void UBossWeapon::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 10; i++)
		BulletObjectPool.Add(GetWorld()->SpawnActor<ABossBullet>(ABossBullet::StaticClass()));
}