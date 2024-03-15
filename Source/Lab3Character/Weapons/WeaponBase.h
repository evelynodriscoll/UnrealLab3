// Copyright (c) 2017 GAM1528. All Rights Reserved.

#pragma once

// Includes the Actor class from the Game Framework, which is the base class for all actors in Unreal Engine.
#include <GameFramework/Actor.h>
// Includes the header file for the ItemBase class, suggesting that this weapon class is a type of item in the game.
#include "ItemBase.h"
// Marks this header file to be preprocessed by Unreal Header Tool (UHT) to generate metadata and serialization code.
#include "WeaponBase.generated.h"

// Declares a dynamic multicast delegate named FOnWeaponFiredSignature. Delegates like this are used for event broadcasting.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFiredSignature);

// Indicates a task to do: Study this class for Lab 3. This is a developer's note or reminder.
//TODO Lab3: Study this Class

// Macro to declare this class as an Unreal Engine class with specific functionalities like reflection and serialization.
UCLASS()
// Declares the AWeaponBase class, specifying it as part of the LAB3CHARACTER module. It inherits from AItemBase.
class LAB3CHARACTER_API AWeaponBase : public AItemBase
{
	// Macro that enables Unreal's reflection system to work with this class.
	GENERATED_BODY()

public:
	// Property to specify the firing rate of the weapon; editable in Unreal Editor's defaults only.
	UPROPERTY(EditDefaultsOnly)
	float FireRate;

	// Property specifying the maximum ammo capacity of the weapon; also visible in Blueprints.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaximumAmmo;

	// Property for the current ammo count of the weapon; also visible in Blueprints.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int CurrentAmmo;

	// Property specifying the type of projectile this weapon fires.
	UPROPERTY(EditDefaultsOnly)
	class UClass* ProjectileType;

	// Delegate property for weapon fired event, allowing other classes to subscribe to this event.
	UPROPERTY(BlueprintAssignable)
	FOnWeaponFiredSignature OnWeaponFired;

public:
	// Function to attach the weapon to a character.
	void Attach(class ACharacterBase* Character);
	// Function to detach the weapon from its character.
	void Detach();

	// Function to handle the trigger pull action.
	void PullTrigger();
	// Function to handle the trigger release action.
	void ReleaseTrigger();

	// Function to get the location of the weapon's muzzle, likely for bullet spawn calculations.
	FVector GetMuzzleLocation() const;

protected:
	// Constructor declaration for AWeaponBase.
	AWeaponBase();

	// Override for the PostInitializeComponents method from AActor.
	virtual void PostInitializeComponents() override;
	// Override for the BeginPlay method from AActor.
	virtual void BeginPlay() override;
	// Override for the Tick method, allowing for per-frame logic.
	virtual void Tick(float DeltaTime) override;

	// Function to handle the firing logic of the weapon.
	void Fire();

private:
	// Function to clear the firing timer, potentially related to the fire rate limiting.
	void ClearFireTimer();

	// Timer handle used for managing firing rate limitations.
	FTimerHandle FireTimer;

	// Primitive component reference, likely used for physical interactions or rendering.
	class UPrimitiveComponent* Primitive;
	// Reference to an arrow component, probably indicating the direction of the muzzle or where the projectile should head towards.
	class UArrowComponent* Muzzle;
};

