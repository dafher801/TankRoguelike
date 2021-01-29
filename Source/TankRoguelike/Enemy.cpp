
#include "Enemy.h"
#include "BaseTank.h"
#include "TankRoguelikeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ShapeComponent.h"

AEnemy::AEnemy(const EUnitTag& UnitTag)
	: AUnit(UnitTag)
{
	Tags.Add("Enemy");

	ShapeCollision->BodyInstance.SetCollisionProfileName("Enemy");
}

void AEnemy::Init()
{
	Super::Init();

	SpawnDefaultController();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player)
		PlayerLocation = Player->GetActorLocation();
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Player && CurrentStatus.HP <= 0.0f)
	{
		Cast<ATankRoguelikeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SpawnItem(GetActorLocation());
		Player->AddScore(Score);
	}

	return DamageAmount;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ATankRoguelikeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetPlayer();
}

void AEnemy::Move()
{
	Super::Move();
}

void AEnemy::Fire(float DeltaTime)
{
	Super::Fire(DeltaTime);
}
