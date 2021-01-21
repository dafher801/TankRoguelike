
#include "Tank.h"
#include "BaseTankWeapon.h"
#include "TankRoguelikeGameMode.h"
#include "Item.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
	: AUnit(EUnitTag::TANK)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Tags.Add("Player");

	Cast<UBoxComponent>(ShapeCollision)->SetBoxExtent(FVector(32.0f, 15.0f, 48.0f), true);
	ShapeCollision->BodyInstance.SetCollisionProfileName("Player");

	static UFlipbookAsset TankBodyIdle = TEXT("/Game/Flipbooks/Tanks/TankBodyIdle");
	BodyFlipbook->SetRelativeLocation(FVector(0.0f, 0.0f, -16.0f));
	BodyFlipbook->SetFlipbook(TankBodyIdle.Object);

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
}

void ATank::Init()
{
	Super::Init();

	Score = UnitData->Score;

	CurrentLeftRightValue = 0.0f;
	CurrentUpDownValue = 0.0f;
	bPressedLeftMouse = false;
	PressedTimeLeftMouse = 0.0f;

	SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
}

void ATank::Tick(float DeltaTime)
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

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveUpDown", this, &ATank::InputUpDown);
	InputComponent->BindAxis("MoveLeftRight", this, &ATank::InputLeftRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATank::PressedLeftMouse);
	InputComponent->BindAction("Fire", IE_Repeat, this, &ATank::RepeatLeftMouse);
	InputComponent->BindAction("Fire", IE_Released, this, &ATank::ReleasedLeftMouse);
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
		Cast<ATankRoguelikeGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GameOver();
	}

	return DamageAmount;
}

void ATank::GetItem(AItem* Item)
{
	CurrentStatus += Item->GetStatus();
}

void ATank::AddScore(int NewScore)
{
	Score += NewScore;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	ShapeCollision->OnComponentHit.AddDynamic(this, &ATank::OnHit);
}

void ATank::Move()
{
	MoveVector = FVector(CurrentUpDownValue, CurrentLeftRightValue, 0.0f);

	if (MoveVector.SizeSquared() > 0.0f)
	{
		BodyRotation = MoveVector.Rotation();
		Super::Move();
	}
}

void ATank::Fire(float DeltaTime)
{
	if (bPressedLeftMouse)
		Super::Fire(DeltaTime);
}

void ATank::InputUpDown(float NewInputValue)
{
	CurrentUpDownValue = NewInputValue;
}

void ATank::InputLeftRight(float NewInputValue)
{
	CurrentLeftRightValue = NewInputValue;
}

void ATank::PressedLeftMouse(FKey key)
{
	bPressedLeftMouse = true;
}

void ATank::RepeatLeftMouse(FKey key)
{
	
}

void ATank::ReleasedLeftMouse(FKey key)
{
	bPressedLeftMouse = false;
}