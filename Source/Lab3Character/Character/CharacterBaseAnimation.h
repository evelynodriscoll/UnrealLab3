// Copyright (c) 2017 GAM1528. All Rights Reserved.

#pragma once

// Includes the base AnimInstance class from the Animation module, allowing this class to inherit from UAnimInstance.
#include <Animation/AnimInstance.h>

// This line includes the header file that Unreal's Header Tool (UHT) uses to generate source code necessary for serialization, reflection, etc., for this animation instance class.
#include "CharacterBaseAnimation.generated.h"

// Indicates a task to do: Study this class for Lab 3. This is a comment for developers.
//TODO Lab3: Study this Class

// The UCLASS macro declares the class to Unreal's reflection system. It marks this class as an Unreal class that inherits from UAnimInstance.
UCLASS()
// Specifies that this class is part of the LAB3CHARACTER module and declares UCharacterBaseAnimation as an animation instance class.
class LAB3CHARACTER_API UCharacterBaseAnimation : public UAnimInstance
{
	// This macro enables Unreal Engine's reflection system to work with this class.
	GENERATED_BODY()

public:
	// A boolean property indicating whether the character has a weapon. It is visible anywhere and readable in Blueprints.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasWeapon;

	// A boolean property indicating whether the character is aiming. It is visible anywhere and readable in Blueprints.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAiming;

	// A boolean property indicating whether the character is moving. It is visible anywhere and readable in Blueprints.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsMoving;

	// A float property indicating the movement speed of the character. It is visible anywhere and readable in Blueprints.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MovementSpeed;

	// A float property indicating the strafing rotation of the character, which could be used for blending animations. It is visible anywhere and readable in Blueprints.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float StrafingRotation;

protected:
	// Constructor declaration for UCharacterBaseAnimation. Sets default values for the class's properties.
	UCharacterBaseAnimation();

	// Overrides the NativeInitializeAnimation method to add custom initialization logic for the animation instance.
	virtual void NativeInitializeAnimation() override;

	// Overrides the NativeUpdateAnimation method to update animation based on the character's state each frame.
	virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:
	// A pointer to the Pawn that owns this animation instance. This can be used to access the character's properties and state.
	APawn* OwningPawn;
};

