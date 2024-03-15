// Copyright (c) 2017 GAM1528. All Rights Reserved.

#include "ProjectileBase.h"

#include "CharacterBase.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Default projectile parameters.*/
	Damage = 10.0f;
	Speed = 1200.0f;
	LifeTime = 1.0f;
}

void AProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//TODO Lab3:
	/* Subscribe to actor's hit event. */
    //SUBSCRIBE to the AActors hit event. Look at this, another way to detect collisions. Un-Comment the line below
	AActor::OnActorHit.AddDynamic(this, &AProjectileBase::OnActorHit);
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//TODO Lab3:
	/* Destroy the projectile after some time.*/
    //Un-Comment the line below
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectileBase::DestroySelf, LifeTime, false);
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TODO Lab3:
	/* Move the projectile in a forward direction.*/
    //Un-Comment the lines below
	/* Retrieve the current location of the actor in the world.*/
	FVector Location = GetActorLocation();

	/* Modify the actor's location by adding a vector that represents movement in the actor's forward direction.
	   This movement is scaled by the actor's speed and the time elapsed since the last frame (DeltaTime),
	   ensuring consistent movement speed regardless of frame rate.*/
	Location += GetActorForwardVector() * Speed * DeltaTime;

	/* Update the actor's world location to the new calculated location.
	   The second parameter "true" indicates that if the actor is moved into another object,
	   it should stop at the point of collision rather than overlap or pass through the object.*/
	SetActorLocation(Location, true);

}

void AProjectileBase::OnActorHit(AActor* Self, AActor* Other, FVector NormalImpulse, const FHitResult& Hit)
{
	//TODO Lab3:
	// Cause damage to the hit actor.
    /*Un-Comment the lines below*/
	/* Check if the 'Other' pointer is not null (i.e., points to an actor) and if 'Other' is of type ACharacterBase or inherits from it.
     This ensures that the code block executes only if 'Other' is a valid character actor.*/
	if (Other != nullptr && Other->IsA<ACharacterBase>())
	{
		/* Initialize a new damage event structure.*/
		/* FDamageEvent is a base class for different damage events, used to pass information about a damage occurrence.*/
		FDamageEvent DamageEvent;

		/* Apply damage to the 'Other' actor.
		 The damage amount is specified by 'Damage'.
		 'DamageEvent' provides context about this specific damage occurrence.
		 The third parameter (nullptr) would typically specify the damage causer's controller if applicable,
		 but here it's set to nullptr, indicating no controller is directly associated with this damage event.
		 The 'this' pointer refers to the actor (or object) that is causing the damage, providing a reference back to the damage source.*/
		//CALL TakeDamage() on Other passing in Damage, DamageEvent, nullptr, this
		Other->TakeDamage(Damage, DamageEvent, nullptr, this);
	}


	/* Destroy self.*/
	Destroy();
}

void AProjectileBase::DestroySelf()
{
	/* Destroy self.*/
	Destroy();
}
