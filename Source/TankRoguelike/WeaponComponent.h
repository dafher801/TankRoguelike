
#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "WeaponDataTable.h"
#include "Containers/Array.h"
#include "WeaponComponent.generated.h"

// Weapon은 각 Unit이 발사체를 발사하면 그 발사체를 관리하는 역할을 담당하며 무기를
// 가지고 있지 않아도 공격을 하는 Unit이라면 UWeaponComponent를 가지고 있습니다.
// 무기가 없는 Unit은 UWeaponComponent의 WeaponFlipbook이 nullptr입니다.
// 총알이 생성되는 위치나 타이밍은 이곳에서 결정합니다.

UCLASS()
class TANKROGUELIKE_API UWeaponComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:

	UWeaponComponent() {}

	UWeaponComponent(const EUnitTag& UnitTag);

	virtual void Init();

	virtual void InitFire(class AUnit* UnitInstigator);

	virtual void Aim();

	virtual bool GetActivated() const;
	virtual void SetActivated(bool Activated);

	virtual void ClearBullets() const;

	virtual void InitSpeedLevel() const;
	virtual void SpeedLevelUp() const;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Visual")
		class UPaperFlipbookComponent* WeaponFlipbook;

	UPROPERTY()
		TArray<class ABullet*> BulletObjectPool;

	struct FWeaponData* WeaponData;

	FVector TargetLocation;
	FRotator FireRotation;

	int BulletNum;

	bool bActivated;
};
