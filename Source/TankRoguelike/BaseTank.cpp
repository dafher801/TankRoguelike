
#include "BaseTank.h"
#include "BaseTankWeapon.h"
#include "TankRoguelikeGameModeBase.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ABaseTank::ABaseTank()
	: AUnit(EUnitTag::TANK)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Tags.Add("Player");

	Cast<UBoxComponent>(ShapeCollision)->SetBoxExtent(FVector(32.0f, 15.0f, 48.0f), true);
	ShapeCollision->BodyInstance.SetCollisionProfileName("Player");

	static UFlipbookAsset BaseTankBodyIdle = TEXT("/Game/Flipbooks/Tanks/TankBodyIdle");
	BodyFlipbook->SetRelativeLocation(FVector(0.0f, 0.0f, -16.0f));
	BodyFlipbook->SetFlipbook(BaseTankBodyIdle.Object);

	WeaponComponent = CreateDefaultSubobject<UBaseTankWeapon>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(BodyFlipbook);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetupAttachment(ShapeCollision);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	for (int i = 0; i < KindOfStatus; i++)
		UpgradeLevel.Add(0);

	BaseMaxHP = UnitData->Status.HP;
	UpgradeRatio = 0.05f;
}

void ABaseTank::Init()
{
	int i, j;

	Super::Init();

	if (!Cast<ATankRoguelikeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetPlaying())
	{
		for (i = 0; i < KindOfStatus; i++)
			UpgradeLevel[i] = 0;
	}

	BaseStatus.HP = BaseMaxHP;

	for (i = 0; i < KindOfStatus; i++)
	{
		for (j = 0; j < UpgradeLevel[i]; j++)
		{
			switch (static_cast<EUpgradeStatus>(i))
			{
			case EUpgradeStatus::HP:
				CurrentStatus.HP += (BaseMaxHP * UpgradeRatio);
				BaseStatus.HP = CurrentStatus.HP;
				break;

			case EUpgradeStatus::ATK:
				CurrentStatus.ATK += (BaseStatus.ATK * UpgradeRatio);
				break;

			case EUpgradeStatus::ATKSPEED:
				CurrentStatus.AttackSpeed += (BaseStatus.AttackSpeed * UpgradeRatio);
				break;

			case EUpgradeStatus::DEF:
				CurrentStatus.DEF += (BaseStatus.DEF * UpgradeRatio * UpgradeRatio);
				break;

			case EUpgradeStatus::MOVESPEED:
				CurrentStatus.MoveSpeed += (BaseStatus.MoveSpeed * UpgradeRatio);
				break;

			case EUpgradeStatus::RANGE:
				CurrentStatus.Range += (BaseStatus.Range * UpgradeRatio);
				break;

			default:
				break;
			}
		}
	}

	Movement->MaxSpeed = CurrentStatus.MoveSpeed;
	Movement->TurningBoost = CurrentStatus.MoveSpeed;

	Score = UnitData->Score;

	CurrentLeftRightValue = 0.0f;
	CurrentUpDownValue = 0.0f;
	bPressedLeftMouse = false;
	PressedTimeLeftMouse = 0.0f;

	SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
}

void ABaseTank::Tick(float DeltaTime)
{
	if (bActivated)
	{
		Super::Tick(DeltaTime);

		Move();

		if (WeaponComponent)
			WeaponComponent->Aim();

		Fire(DeltaTime);
	}
}

void ABaseTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveUpDown", this, &ABaseTank::InputUpDown);
	InputComponent->BindAxis("MoveLeftRight", this, &ABaseTank::InputLeftRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ABaseTank::PressedLeftMouse);
	InputComponent->BindAction("Fire", IE_Repeat, this, &ABaseTank::RepeatLeftMouse);
	InputComponent->BindAction("Fire", IE_Released, this, &ABaseTank::ReleasedLeftMouse);
}

float ABaseTank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 현재 탱크의 가로 : 세로 비율은 2 : 3 이다.

	float Degree = FMath::Abs((DamageCauser->GetActorLocation() -
		GetActorLocation()).Rotation().Yaw - BodyRotation.Yaw);

	if (Degree <= FVector(3.0f, 2.0f, 0.0f).Rotation().Yaw)
	{
		DamageAmount *= 0.05f;
	}
	else if (Degree > FVector(-3.0f, 2.0f, 0.0f).Rotation().Yaw)
	{
		DamageAmount *= 1.5f;
	}

	DamageAmount -= CurrentStatus.DEF;
	CurrentStatus.HP -= DamageAmount;

	if (CurrentStatus.HP <= 0.0f)
	{
		CurrentStatus.HP = 0.0f;
		Cast<ATankRoguelikeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GameOver();
	}

	return DamageAmount;
}

void ABaseTank::GetItem(AItem* Item)
{
	CurrentStatus += Item->GetStatus();
}

void ABaseTank::AddScore(int NewScore)
{
	Score += NewScore;
}

void ABaseTank::Upgrade(EUpgradeStatus UpgradeStatus)
{
	if (Cast<ATankRoguelikeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->PayScore())
		UpgradeLevel[UpgradeStatus]++;
}

void ABaseTank::BeginPlay()
{
	Super::BeginPlay();

	ShapeCollision->OnComponentHit.AddDynamic(this, &ABaseTank::OnHit);
}

void ABaseTank::Move()
{
	MoveVector = FVector(CurrentUpDownValue, CurrentLeftRightValue, 0.0f);

	if (MoveVector.SizeSquared() > 0.0f)
	{
		BodyRotation = MoveVector.Rotation();
		Super::Move();
	}
}

void ABaseTank::Fire(float DeltaTime)
{
	if (bPressedLeftMouse)
		Super::Fire(DeltaTime);
}

void ABaseTank::InputUpDown(float NewInputValue)
{
	CurrentUpDownValue = NewInputValue;
}

void ABaseTank::InputLeftRight(float NewInputValue)
{
	CurrentLeftRightValue = NewInputValue;
}

void ABaseTank::PressedLeftMouse(FKey key)
{
	bPressedLeftMouse = true;
}

void ABaseTank::RepeatLeftMouse(FKey key)
{

}

void ABaseTank::ReleasedLeftMouse(FKey key)
{
	bPressedLeftMouse = false;
}