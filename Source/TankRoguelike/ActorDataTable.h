
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ActorDataTable.generated.h"

class UPaperFlipbook;

typedef ConstructorHelpers::FObjectFinder<UPaperFlipbook> UFlipbookAsset;
typedef ConstructorHelpers::FObjectFinder<UDataTable> UDataTableAsset;

UENUM()
enum class EActorCollisionShape
{
	BOX,
	SPHERE,
	CAPSULE
};

UENUM()
enum class EUnitTag
{
	TANK,
	GREENFLYINGBOOK,
	REDFLYINGBOOK,
	BLUEFLYINGBOOK,
	YELLOWFLYINGBOOK
};

USTRUCT()
struct FStatus : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float Range;

	FORCEINLINE struct FStatus operator*(float Ratio)
	{
		FStatus ret;

		ret.HP = HP * Ratio;
		ret.ATK = ATK * Ratio;
		ret.AttackSpeed = AttackSpeed * Ratio;
		ret.DEF = DEF * Ratio;
		ret.MoveSpeed = MoveSpeed * Ratio;
		ret.Range = Range * Ratio;

		return ret;
	}

	FORCEINLINE struct FStatus& operator+=(const FStatus& Status)
	{
		HP += Status.HP;
		ATK += Status.ATK;
		DEF += Status.DEF;
		MoveSpeed += Status.MoveSpeed;
		AttackSpeed += Status.AttackSpeed;
		Range += Status.Range;

		return *this;
	}
};

USTRUCT()
struct FActorData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Status")
		FStatus Status;

	UPROPERTY(EditAnywhere, Category = "ActorBase")
		EActorCollisionShape ActorCollisionShape;

	UPROPERTY(EditAnywhere, Category = "Transform")
		FVector Scale;

	UPROPERTY(EditAnywhere, Category = "Transform")
		FRotator CollisionRotation;

	UPROPERTY(EditAnywhere, Category = "Transform")
		FRotator FlipbookRotation;

	UPROPERTY(EditAnywhere, Category = "Transform")
		FRotator DirectionRotation;
};

UCLASS()
class TANKROGUELIKE_API UActorDataTable : public UObject
{
	GENERATED_BODY()
};
