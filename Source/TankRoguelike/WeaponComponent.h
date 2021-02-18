
#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "WeaponDataTable.h"
#include "Containers/Array.h"
#include "WeaponComponent.generated.h"

// Weapon�� �� Unit�� �߻�ü�� �߻��ϸ� �� �߻�ü�� �����ϴ� ������ ����ϸ� ���⸦
// ������ ���� �ʾƵ� ������ �ϴ� Unit�̶�� UWeaponComponent�� ������ �ֽ��ϴ�.
// ���Ⱑ ���� Unit�� UWeaponComponent�� WeaponFlipbook�� nullptr�Դϴ�.
// �Ѿ��� �����Ǵ� ��ġ�� Ÿ�̹��� �̰����� �����մϴ�.

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
