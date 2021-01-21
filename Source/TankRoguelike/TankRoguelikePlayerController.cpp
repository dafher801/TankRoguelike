
#include "TankRoguelikePlayerController.h"
#include "Components/InputComponent.h"

ATankRoguelikePlayerController::ATankRoguelikePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void ATankRoguelikePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
}

void ATankRoguelikePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}