// Copyright (c) 2017 GAM1528. All Rights Reserved.

#pragma once

// Includes the Character class from the Game Framework, providing base character functionality such as movement and animation.
#include <GameFramework/Character.h>

// Unreal Engine's way of allowing the UHT (Unreal Header Tool) to generate source code necessary for serialization, reflection, etc.
#include "CharacterBase.generated.h"

// Indicates a task to do: Study the class for Lab 3. This is a comment for developers.
//TODO Lab3: Study this Class

// Macro to declare a new class ACharacterBase that inherits from ACharacter. The UCLASS macro is used for reflection and serialization.
UCLASS()
// Specifies that this class is part of the LAB3CHARACTER module and declares ACharacterBase as a character class.
class LAB3CHARACTER_API ACharacterBase : public ACharacter
{
	// Macro to allow reflection and serialization for member variables and functions within the class.
	GENERATED_BODY()

public:
	// Property macro to make the variable editable in the Unreal Editor's defaults only. Holds the maximum walking speed of the character.
	UPROPERTY(EditDefaultsOnly)
	float MaxWalkSpeed;

	// Property macro for the maximum jogging speed, editable in the Unreal Editor's defaults only.
	UPROPERTY(EditDefaultsOnly)
	float MaxJogSpeed;

	// Property for the maximum distance at which the character can pick up objects, editable in defaults only.
	UPROPERTY(EditDefaultsOnly)
	float MaxPickUpDistance;

	// Property for the animation sequence when firing from the hip, editable in defaults only.
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* FireHipAnimation;

	// Property for the animation sequence when firing while aiming, editable in defaults only.
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* FireAimAnimation;

	// Function macro for a function that does not modify the object. Returns the currently equipped weapon.
	UFUNCTION(BlueprintPure)
	class AWeaponBase* GetCurrentWeapon();

	// Function to move the character in a direction with a specific scale.
	void Move(FVector Direction, float Scale);
	// Function to fire the weapon.
	void Fire(bool Toggle);
	// Function to toggle aiming mode.
	void Aim(bool Toggle);

	// Function for interacting with other actors.
	void Interact(AActor* Actor);

	// Returns the skeletal mesh component of the character.
	class USkeletalMeshComponent* GetSkeletalMesh();

	// Overrides the SetupPlayerInputComponent to bind functionality to input.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Property for the maximum health of the character, readable in Blueprints.
	UPROPERTY(EditDefaultsOnly)
	float MaximumHealth;

	// Indicates a task to do: Add functionality related to Lab 3. This is a reminder comment for developers.
	//TODO Lab3:
	// Property for the current health of the character, readable in Blueprints.
	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;

protected:
	// Constructor declaration for ACharacterBase.
	ACharacterBase();

	// Overrides the PostInitializeComponents function.
	virtual void PostInitializeComponents() override;
	// Overrides the BeginPlay function.
	virtual void BeginPlay() override;
	// Overrides the Tick function to add custom behavior on every game tick.
	virtual void Tick(float DeltaTime) override;

	// Function to handle the OnWeaponFired event.
	UFUNCTION()
	void OnWeaponFired();

	// Function to handle the OnDeath event.
	UFUNCTION()
	void OnDeath();

	// Function to handle taking damage, with parameters specifying the context of the damage.
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

private:
	// Function to make the character hold a weapon.
	void HoldWeapon(class AWeaponBase* Weapon);
	// Function to drop the currently held weapon.
	void DropWeapon();

	// Function to update movement logic based on the DeltaTime.
	void UpdateMovement(float DeltaTime);
	// Function to update the character's animations based on current state.
	void UpdateAnimation();

	// Function to move the character vertically.
	void MoveVertical(float Scale);
	// Function to move the character horizontally.
	void MoveHorizontal(float Scale);

	// Class component declarations.
	class USkeletalMeshComponent* SkeletalMesh;
	class UCharacterBaseAnimation* AnimationInstance;

	// Property for the currently held weapon, not exposed to the Unreal Editor.
	UPROPERTY()
	class AWeaponBase* CurrentWeapon;

	// Boolean flag to indicate aiming state.
	bool bIsAiming;
	// Boolean flag to indicate firing state.
	bool bIsFiring;

	// Boolean flag to indicate if the character has a weapon.
	bool bHasWeapon;
};
