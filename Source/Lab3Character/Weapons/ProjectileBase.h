// Copyright (c) 2017 GAM1528. All Rights Reserved.

#pragma once

// Includes the base actor class from the game framework, allowing this class to inherit from AActor.
#include <GameFramework/Actor.h>

// This line includes the header file that Unreal's Header Tool (UHT) uses to generate source code necessary for serialization, reflection, etc., for this projectile class.
#include "ProjectileBase.generated.h"

// Indicates a task to do: Study this class for Lab 3. This is a comment for developers.
//TODO Lab3: Study this Class

// The UCLASS macro declares the class to Unreal's reflection system. It marks this class as an Unreal class that inherits from AActor.
UCLASS()
// Specifies that this class is part of the LAB3CHARACTER module and declares AProjectileBase as an actor class.
class LAB3CHARACTER_API AProjectileBase : public AActor
{
	// This macro enables Unreal Engine's reflection system to work with this class.
	GENERATED_BODY()

public:
	// Declares a property to hold the damage value of the projectile, editable in Unreal Editor's defaults only.
	UPROPERTY(EditDefaultsOnly)
	float Damage;

	// Declares a property for the speed of the projectile, editable in Unreal Editor's defaults only.
	UPROPERTY(EditDefaultsOnly)
	float Speed;

	// Declares a property for the lifetime of the projectile, after which it should be destroyed, editable in Unreal Editor's defaults only.
	UPROPERTY(EditDefaultsOnly)
	float LifeTime;

protected:
	// Constructor declaration for AProjectileBase. Sets default values for the projectile's properties.
	AProjectileBase();

	// Overrides the PostInitializeComponents method to customize initialization logic that runs after component initialization.
	virtual void PostInitializeComponents() override;

	// Overrides the BeginPlay method to add custom logic at the start of the game.
	virtual void BeginPlay() override;

	// Overrides the Tick method to add custom behavior on every game tick.
	virtual void Tick(float DeltaTime) override;

	// Function to handle the event when the projectile hits another actor.
	UFUNCTION()
	void OnActorHit(AActor* Self, AActor* Other, FVector NormalImpulse, const FHitResult& Hit);

private:
	// Function to destroy the projectile. This can be called when the projectile's lifetime expires or it hits something.
	void DestroySelf();

private:
	// Timer handle for managing the lifetime of the projectile. Used to schedule destruction of the projectile.
	FTimerHandle Timer;
};
