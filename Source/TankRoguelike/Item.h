
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDataTable.h"
#include "Item.generated.h"

UCLASS()
class TANKROGUELIKE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem();

	virtual void Init();

	virtual void Tick(float DeltaTime) override;

	FStatus GetStatus() const;

	bool GetActivated() const;
	void SetActivated(bool Activated);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Collision")
		class UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Visual")
		class UPaperFlipbookComponent* ItemFlipbook;

	UPROPERTY(EditAnywhere, Category = "Status")
		FStatus Status;

	UPROPERTY()
		FTimerHandle TimerHandle;

	struct FItemData* ItemData;

	bool bActivated;
};
