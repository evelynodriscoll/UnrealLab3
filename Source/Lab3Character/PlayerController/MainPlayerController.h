#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

// Declares a class to be recognized by Unreal's Object system, allowing it to utilize Unreal's features such as serialization and reflection.
UCLASS()
// Declares a class that extends APlayerController, specifying it as part of the LAB3CHARACTER_API module. APlayerController is a class that handles player input and pawn control.
class LAB3CHARACTER_API AMainPlayerController : public APlayerController
{
	// Macro that enables Unreal's reflection system to work with this class, allowing various engine features to interact with it, such as the editor properties window.
	GENERATED_BODY()

public:
	// Constructor declaration for AMainPlayerController.
	AMainPlayerController();

	// Overrides the AcknowledgePossession method from APlayerController to provide custom behavior when the controller possesses a pawn.
	virtual void AcknowledgePossession(class APawn* P) override;

protected:
	// Overrides the OnPossess method to define custom behavior when a new pawn is possessed.
	virtual void OnPossess(APawn* aPawn) override;

	// Overrides the OnUnPossess method to define custom behavior when the controller no longer possesses a pawn.
	virtual void OnUnPossess() override;

	// Overrides SetupInputComponent to configure input bindings.
	virtual void SetupInputComponent() override;

	// Overrides BeginPlay to add custom initialization logic at the start of the game.
	virtual void BeginPlay() override;

	// Pointer to the main character pawn that this controller is managing.
	class ACharacter* TheMainPawn;

	// Function to handle the input for interaction (e.g., picking up objects, talking to NPCs).
	void InteractPressed();

	// Function to handle the input for beginning to fire a weapon.
	void FirePressed();

	// Function to handle the input for stopping the firing of a weapon.
	void FireReleased();

	// Function to handle the input for beginning to aim.
	void AimPressed();

	// Function to handle the input for stopping aiming.
	void AimReleased();

	// Function to handle input from moving the right thumbstick on a controller. Could be used for camera control or other input.
	void InputThumbstickRight(float Value);
};

