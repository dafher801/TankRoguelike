
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UnitDataTable.h"
#include "Unit.generated.h"

UCLASS()
class TANKROGUELIKE_API AUnit : public APawn
{
	GENERATED_BODY()

public:

	AUnit() {}

	AUnit(const EUnitTag& UnitTag);

	virtual void Init();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
		virtual void OnHit(class UPrimitiveComponent* OtherComp, class AActor* OtherActor, class UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit);

	bool GetActivated() const;
	void SetActivated(bool Activated);

	UFUNCTION(BlueprintCallable)
		FStatus GetBaseStatus() const;

	UFUNCTION(BlueprintCallable)
		FStatus GetCurrentStatus() const;

	UFUNCTION(BlueprintCallable)
		int GetScore() const;

	class UWeaponComponent* GetWeaponComponent() const;

protected:

	virtual void BeginPlay() override;

	// 아래의 두 함수는 무조건 Tick함수 내에서 실행되어야 합니다.
	virtual void Move();
	virtual void Fire(float DelatTime);

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Collision")
		class UShapeComponent* ShapeCollision;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Visual")
		class UPaperFlipbookComponent* BodyFlipbook;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Socket")
		class UWeaponComponent* WeaponComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Helper")
		class UArrowComponent* Direction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement")
		class UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere, Category = "Status")
		FStatus BaseStatus;

	UPROPERTY(EditAnywhere, Category = "Status")
		FStatus CurrentStatus;

	struct FUnitData* UnitData;

	EUnitTag UnitTag;

	FVector MoveVector;
	FRotator BodyRotation;

	float TimeElapsedSinceAttack;
	bool bIsEnableAttack;

	bool bActivated;

	int Score;
};