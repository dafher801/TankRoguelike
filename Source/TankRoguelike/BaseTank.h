
#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "BaseTank.generated.h"

UENUM(BlueprintType)
enum EUpgradeStatus
{
	HP,
	ATK,
	ATKSPEED,
	DEF,
	MOVESPEED,
	RANGE
};

UCLASS()
class TANKROGUELIKE_API ABaseTank : public AUnit
{
	GENERATED_BODY()

public:

	ABaseTank();

	virtual void Init() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void GetItem(class AItem* Item);

	void AddScore(int NewScore);

	UFUNCTION(BlueprintCallable)
		void Upgrade(EUpgradeStatus UpgradeStatus);

	void InitLevel();

protected:

	virtual void BeginPlay() override;

	// �Ʒ��� �� �Լ��� ������ Tick�Լ� ������ ����Ǿ�� �մϴ�.
	virtual void Move() override;
	virtual void Fire(float DeltaTime) override;

	virtual void InputUpDown(float NewInputValue);
	virtual void InputLeftRight(float NewInputValue);

	virtual void PressedLeftMouse(FKey key);
	virtual void RepeatLeftMouse(FKey key);
	virtual void ReleasedLeftMouse(FKey key);

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
		class UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly)
		TArray<int> UpgradeLevel;

	TArray<class AItem*> Items;

	// �÷��̾� ����Ű �Է�
	float CurrentUpDownValue;
	float CurrentLeftRightValue;

	bool bPressedLeftMouse;
	float PressedTimeLeftMouse;

	float BaseMaxHP;
};
