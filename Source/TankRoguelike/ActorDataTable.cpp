
#include "ActorDataTable.h"

AActorDataTable::AActorDataTable()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AActorDataTable::BeginPlay()
{
	Super::BeginPlay();
}

void AActorDataTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}