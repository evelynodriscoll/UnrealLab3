#include "MainPlayerController.h"

#include "CharacterBase.h"
#include "GameFramework/PlayerInput.h"

// Sets default values
// Constructor definition for AMainPlayerController. It's empty and serves to initialize the controller instance.
AMainPlayerController::AMainPlayerController()
{

}

// Overrides the AcknowledgePossession method from APlayerController to customize the behavior when the controller possesses a pawn.
void AMainPlayerController::AcknowledgePossession(APawn* P)
{
	// Calls the base class implementation of AcknowledgePossession.
	Super::AcknowledgePossession(P);
	// Casts the pawn to ACharacter type and assigns it to TheMainPawn. This is used to keep track of the currently controlled character pawn.
	TheMainPawn = Cast<ACharacter>(P);

}

// Overrides the OnPossess method to customize behavior when a new pawn is possessed.
void AMainPlayerController::OnPossess(APawn* aPawn)
{
	// Calls the base class implementation of OnPossess.
	Super::OnPossess(aPawn);
	// Casts the possessed pawn to ACharacter type and stores it in TheMainPawn.
	TheMainPawn = Cast<ACharacter>(aPawn);

}

// Overrides the OnUnPossess method to define custom behavior when the controller no longer possesses a pawn.
void AMainPlayerController::OnUnPossess()
{
	// Calls the base class implementation of OnUnPossess.
	Super::OnUnPossess();
}

// SetupInputComponent is overridden to configure the input bindings for the player controller.
void AMainPlayerController::SetupInputComponent()
{
	// Calls the base class implementation to ensure default input components are set up.
	Super::SetupInputComponent();
	//TODO Lab3:
	// Checks if InputComponent is valid before setting up input bindings.
	if (InputComponent)
	{
		// Bind actions and axes to their respective handler functions within this controller.
		// Example bindings for movement and camera are commented out for reference.

		// Binds the "Interact" action to the InteractPressed function for when the button is pressed.
		InputComponent->BindAction("Interact", IE_Pressed, this, &AMainPlayerController::InteractPressed);

		// Binds the "Fire" action to the FirePressed and FireReleased functions.
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMainPlayerController::FirePressed);
		InputComponent->BindAction("Fire", IE_Released, this, &AMainPlayerController::FireReleased);

		// Binds the "Aim" action to the AimPressed and AimReleased functions.
		InputComponent->BindAction("Aim", IE_Pressed, this, &AMainPlayerController::AimPressed);
		InputComponent->BindAction("Aim", IE_Released, this, &AMainPlayerController::AimReleased);

		// Binds the movement of the thumbstick (or potentially mouse movement in this context) to the InputThumbstickRight function.
		InputComponent->BindAxis("ThumbstickY", this, &AMainPlayerController::InputThumbstickRight);
		InputComponent->BindAxis("ThumbstickX", this, &AMainPlayerController::InputThumbstickRight);
	}
}

// BeginPlay is overridden to add custom initialization logic at the start of the game.
void AMainPlayerController::BeginPlay()
{
	//TODO Lab3:
	// Calls the base class implementation of BeginPlay.
	Super::BeginPlay();
	// Enables the mouse cursor to be shown on the screen.
	bShowMouseCursor = true;
	// Enables click events to be registered.
	bEnableClickEvents = true;
	// Enables mouse-over events to be registered.
	bEnableMouseOverEvents = true;
	// Executes a console command to show collision boundaries in the game for debugging.
	ConsoleCommand("show collision");
	// Setting the input mode to game only could be done here to disable UI interaction; it's commented out for reference.
	//SetInputMode(FInputModeGameOnly());
}

// InteractPressed is called when the "Interact" action is triggered. It handles interaction with objects in the game world.
void AMainPlayerController::InteractPressed()
{
	
	// Checks if there's a controlled pawn.
	if (TheMainPawn)
	{
		// Attempts to cast the main pawn to ACharacterBase to access specific character functionality.
		ACharacterBase* TheCharacter = Cast<ACharacterBase>(TheMainPawn);
		// If the cast fails or TheCharacter is nullptr, exit the function.
		if (!TheCharacter)
			return;

		//TODO Lab3 AMainPlayerController::InteractPressed(...):
		// Performs a hit trace under the cursor to detect interactable objects in the world.
		FHitResult TraceResult;
		//CALL GetHitResultUnderCursorByChannel() passing in UEngineTypes::ConvertToTraceType(ECC_WorldDynamic), false, TraceResult
		

		// Calls the Interact function on the character, passing in the actor that was hit by the trace, if any.
		TheCharacter->Interact(TraceResult.GetActor());
	}
}

// FirePressed is called when the "Fire" action is initiated, handling the start of firing a weapon.
void AMainPlayerController::FirePressed()
{
	//TODO Lab3:
	// Checks if there's a controlled pawn.
	if (TheMainPawn)
	{
		// Attempts to cast the main pawn to ACharacterBase to use specific functionality.
		ACharacterBase* TheCharacter = Cast<ACharacterBase>(TheMainPawn);
		// If the cast fails or TheCharacter is nullptr, exit the function.
		if (!TheCharacter)
			return;
		// Calls the Fire function on the character, passing in true to start firing.
		TheCharacter->Fire(true);
	}
}

// FireReleased is called when the "Fire" action is released, handling the stop of firing a weapon.
void AMainPlayerController::FireReleased()
{
	//TODO Lab3:
	// Checks if there's a controlled pawn.
	if (TheMainPawn)
	{
		// Attempts to cast the main pawn to ACharacterBase to use specific functionality.
		ACharacterBase* TheCharacter = Cast<ACharacterBase>(TheMainPawn);
		// If the cast fails or TheCharacter is nullptr, exit the function.
		if (!TheCharacter)
			return;
		// Calls the Fire function on the character, passing in false to stop firing.
		TheCharacter->Fire(false);
	}
}

// AimPressed is called when the "Aim" action is initiated, handling the start of aiming.
void AMainPlayerController::AimPressed()
{
	//TODO Lab3:
	// Checks if there's a controlled pawn.
	if (TheMainPawn)
	{
		// Attempts to cast the main pawn to ACharacterBase to use specific functionality.
		ACharacterBase* TheCharacter = Cast<ACharacterBase>(TheMainPawn);
		// If the cast fails or TheCharacter is nullptr, exit the function.
		if (!TheCharacter)
			return;
		// Calls the Aim function on the character, passing in true to start aiming.
		TheCharacter->Aim(true);
	}
}

// AimReleased is called when the "Aim" action is released, handling the stop of aiming.
void AMainPlayerController::AimReleased()
{
	//TODO Lab3:
	// Checks if there's a controlled pawn.
	if (TheMainPawn)
	{
		// Attempts to cast the main pawn to ACharacterBase to use specific functionality.
		ACharacterBase* TheCharacter = Cast<ACharacterBase>(TheMainPawn);
		// If the cast fails or TheCharacter is nullptr, exit the function.
		if (!TheCharacter)
			return;
		// Calls the Aim function on the character, passing in false to stop aiming.
		TheCharacter->Aim(false);
	}
}

// InputThumbstickRight is called to handle input from the right thumbstick or equivalent input mechanism.
void AMainPlayerController::InputThumbstickRight(float Value)
{
	//TODO Lab3:
	// Checks if the input value is not zero, indicating movement.
	if (Value != 0)
	{
		// Retrieves the current mouse position.
		float MouseX;
		float MouseY;
		GetMousePosition(MouseX, MouseY);

		// Calculates new mouse positions based on thumbstick input, scaled by a factor for sensitivity adjustment.
		float ThumbXValue = InputComponent->GetAxisValue("ThumbstickX") * 4.0f;
		float ThumbYValue = InputComponent->GetAxisValue("ThumbstickY") * 4.0f;

		float MouseValueX = MouseX + ThumbXValue;
		float MouseValueY = MouseY + ThumbYValue;

		// Sets the new mouse location to the calculated values, rounding to the nearest integer.
		SetMouseLocation(FMath::RoundToInt(MouseValueX), FMath::RoundToInt(MouseValueY));
	}

}


