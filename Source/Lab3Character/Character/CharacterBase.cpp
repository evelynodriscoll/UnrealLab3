// Copyright (c) 2017 GAM1528. All Rights Reserved.

#include "CharacterBase.h"
#include "Lab3Character.h"
#include "CharacterBaseAnimation.h"

#include <GameFramework/PlayerController.h>
//#include "Gameplay/Health/HealthComponent.h"
#include "Weapons/WeaponBase.h"
#include "ItemBase.h"

/*
Setup the character defaults
*/
ACharacterBase::ACharacterBase() :
	SkeletalMesh(nullptr),
	AnimationInstance(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	//TODO Lab3:
	/* Set default movement speed. */
	MaxWalkSpeed = 140.0f;
	MaxJogSpeed = 280.0f;

	GetCharacterMovement()->MaxWalkSpeed = MaxJogSpeed;

	/* Do not update the controller's rotation yaw.*/
	/* Has to be disabled for "Orient Rotation to Movement" to work.*/
	bUseControllerRotationYaw = false;

	/* Rotate the character during movement by default.*/
	GetCharacterMovement()->bOrientRotationToMovement = true;

	/* Character interaction values. */
	MaxPickUpDistance = 200.0f;

	/* Character weapon handling values.*/
	CurrentWeapon = nullptr;

	bIsAiming = false;
	bIsFiring = false;
}

/*
Allow actors to initialize themselves on the C++ side
https://api.unrealengine.com/INT/API/Runtime/Engine/GameFramework/AActor/PostInitializeComponents/index.html
*/
void ACharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//TODO Lab3 ACharacterBase::PostInitializeComponents():
	/*Retrieve the skeletal mesh component. */
    //SET SkeletalMesh to the return value of GetMesh()

	SkeletalMesh = GetMesh();
	
    if(SkeletalMesh !=nullptr)
	
	{
		check(SkeletalMesh != nullptr && "Character does not have a skeletal mesh component!");

		/* Retrieve the animation instance.*/
        //SET AnimationInstance to the SkeletalMesh's Animation Instance --> Cast<UCharacterBaseAnimation>(SkeletalMesh->GetAnimInstance())
		AnimationInstance = Cast<UCharacterBaseAnimation>(SkeletalMesh->GetAnimInstance());
	
		check(AnimationInstance != nullptr && "Character does not have an animation instance!");
	}
    //ENDIF

	/* Attempts to find the first USpringArmComponent attached to this actor.*/
	USpringArmComponent* SpringArm = FindComponentByClass<USpringArmComponent>();

	/* Check if a SpringArm component was successfully found.*/
	if (SpringArm)
	{
		/* Disables collision testing for the spring arm, allowing it to move through objects without being obstructed.*/
		SpringArm->bDoCollisionTest = false;

		/* Prevents the spring arm from inheriting pitch from its parent component, allowing for independent pitch control.*/
		SpringArm->bInheritPitch = false;

		/* Prevents the spring arm from inheriting yaw from its parent component, allowing for independent yaw control.*/
		SpringArm->bInheritYaw = false;

		/* Prevents the spring arm from inheriting roll from its parent component, allowing for independent roll control.*/
		SpringArm->bInheritRoll = false;

		/* Enables camera lag, creating a trailing effect as the camera follows the actor, enhancing the feeling of motion.*/
		SpringArm->bEnableCameraLag = true;

		/* Sets the speed of the camera lag, determining how quickly the camera catches up to the moving target.*/
		SpringArm->CameraLagSpeed = 3.0f;
	}

}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//TODO Lab3 ACharacterBase::BeginPlay():
	/* Enables the actor to be damaged. By default, actors might not be susceptible to damage without explicitly enabling this.*/
	//CALL SetCanBeDamaged() passing in true
	SetCanBeDamaged(true);
	

	/* Registers a dynamic delegate for the OnTakeAnyDamage event. When the actor takes any form of damage, the OnTakeDamage function within the ACharacterBase class will be called.
	 This setup is essential for implementing custom damage handling logic.*/
	//ADD &ACharacterBase::OnTakeDamage as a Dynamic function to the OnTakeAnyDamage event

	this->OnTakeAnyDamage.AddDynamic(this,
		&ACharacterBase::OnTakeDamage);


}


void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveVertical);
	InputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveHorizontal);

}

/*
In Tick, we will be Controlling the movement states for the Character, as well as setting the Animation States based on the character movement,
Such as while Aiming, Firing the weapon while moving.
*/
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Handle movement orientation and speed. */
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = MaxJogSpeed;
    
	//TODO Lab3 ACharacterBase::Tick(...):
	UpdateMovement(DeltaTime);

	UpdateAnimation();
	
}

// Function to update the character's movement and orientation based on aiming or firing state.
void ACharacterBase::UpdateMovement(float DeltaTime)
{
	//TODO Lab3 ACharacterBase::UpdateMovement():
	/* Check if the character currently has a weapon equipped.*/
	//SET bHasWeapon to the value of CurrentWeapon != nullptr

	if (CurrentWeapon != nullptr) {
		bHasWeapon = true;
	}
	

	/* If no weapon is equipped, exit the function early as no further movement updates are necessary.*/
	if (CurrentWeapon == nullptr) return;

	/* Retrieve the character's movement component, which controls all movement behavior.*/
	//DECLARE a auto variable called CharMovement and SET to the return value of GetCharacterMovement()

	auto CharMovement = GetCharacterMovement();
	

	/* When the character is aiming or firing, we need to adjust their movement and orientation.*/
	if (bIsAiming || bIsFiring)
	{
		/* Prevent the character from orienting its rotation automatically to its movement direction.*/
		//SET CharMovement's bOrientRotationToMovement property to false
		CharMovement->bOrientRotationToMovement = false;
	

		/* Adjust the character's maximum walk speed based on whether it is firing. If firing, reduce speed.*/
		//SET CharMovement's MaxWalkSpeed to MaxWalkSpeed * 0.8f if bIsFiring is true, otherwise set it to MaxWalkSpeed

		if (bIsFiring) {
			CharMovement->MaxWalkSpeed = MaxWalkSpeed * 0.8f;
		}
		else {
			CharMovement->MaxWalkSpeed = MaxWalkSpeed;
		}
	

		/* Attempt to cast the character's controller to APlayerController to access player-specific functions.*/
		//DECLARE a auto variable called PlayerController and ASSIGN it to the return value of GetController() (CAST)
		auto PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			/* Variables to store the mouse's world position and direction.*/
			//DECLARE two temporary variables of type FVector, one called MouseLocation and the other called MouseDirection
			FVector MouseLocation, MouseDirection;
			/* Convert the mouse position into a world space position and direction.*/
			if (PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection))
			{
				/* Calculate a plane based on the weapon's muzzle location for intersection calculation.*/
				//DECLARE a variable called PlaneOrigin of type FVector and SET to the return value of CurrentWeapon->GetMuzzleLocation()
				FVector PlaneOrigin = CurrentWeapon->GetMuzzleLocation();
				
				/* Determine a far away point along the mouse direction for the line-plane intersection.*/
				//DECLARE a variable called LineEnd of type FVector and SET it to the value of MouseLocation + MouseDirection * 10000.0f
				FVector LineEnd = MouseLocation + MouseDirection * 10000.0f;
				
				/* Calculate the intersection point where the character should look towards.*/
				//DECLARE a variable called LookLocation of type FVector and SET it to the return value of FMath::LinePlaneIntersection(MouseLocation, LineEnd, PlaneOrigin, FVector(0.0f, 0.0f, 1.0f))
				FVector LookLocation = FMath::LinePlaneIntersection(MouseLocation, LineEnd, PlaneOrigin, FVector(0.0f, 0.0f, 1.0f));
				

				/* Calculate the rotation from the character to the look location, ignoring pitch and roll for a flat rotation.*/
				//DECLARE a variable called LookRotation of type FRotator and SET it to the value of (LookLocation - GetActorLocation()).Rotation()

				FRotator LookRotation = (LookLocation - GetActorLocation()).Rotation();
				
				//ZERO out LookRotation.Pitch and LookRotation.Roll

				LookRotation.Pitch = 0.0f;
				LookRotation.Roll = 0.0f;
				

				/* Smoothly interpolate the character's rotation towards the desired look rotation.*/
				//CALL SetActorRotation() Interpolating the rotation using FMath::RInterpTo(GetActorRotation(), LookRotation, DeltaTime, 10.0f)
				SetActorRotation(FMath::RInterpTo(GetActorRotation(), LookRotation, DeltaTime, 10.0f));
				
			}
		}
	}
}


void ACharacterBase::UpdateAnimation()
{
	//TODO Lab3 ACharacterBase::UpdateAnimation():
	/* Directly transfer relevant character states to the AnimationInstance*/
	AnimationInstance->bHasWeapon = bHasWeapon;
	AnimationInstance->bIsAiming = bIsAiming;

	/* Calculate current speed and moving state*/
	//DECLARE a float called CurrentSpeed and SET it to the return value of GetVelocity().Size()
	float CurrentSpeed = GetVelocity().Size();
	
	//DECLARE a bool called bIsMoving and SET it to the value of CurrentSpeed > 0.0f && GetCharacterMovement()->IsMovingOnGround()
	bool bIsMoving = false;
	if (CurrentSpeed > 0.0f && GetCharacterMovement()->IsMovingOnGround()) {
		bIsMoving = true;
	}

	/* Update AnimationInstance movement parameters*/
	//UNCOMMENT
	AnimationInstance->bIsMoving = bIsMoving;
	AnimationInstance->MovementSpeed = bIsMoving ? CurrentSpeed : 0.0f;

	/* Calculate and set strafing rotation*/
	//DECLARE a FVector called MovementDirection and SET it to the return value of GetLastMovementInputVector()
	FVector MovementDirection = GetLastMovementInputVector();
	if (!MovementDirection.IsNearlyZero())
	{
		
		/* Get the forward vector of the actor, which represents the direction the actor is facing in the world space.*/
		//DECLARE a FVector called CharacterDirection and SET it to the return value of GetActorForwardVector()
		FVector CharacterDirection = GetActorForwardVector();
		

		/* Calculate the rotation needed for strafing movement.
		 This involves finding the angle between the movement direction (usually from input) and the character's forward direction.
		 MovementDirection is presumed to be a vector representing the desired movement direction.
		 The Y component of these vectors is used along with the X component to calculate the atan2 (arctangent of two parameters, y/x, considering the correct quadrant),
		 giving us an angle in radians. The difference between these angles gives us the strafing rotation relative to the character's current facing direction.
		*/
		//DECLARE a variable called StrafingRotation of type float and SET it to the value of  FMath::Atan2(MovementDirection.Y, MovementDirection.X) - FMath::Atan2(CharacterDirection.Y, CharacterDirection.X)
		float StrafingRotation = FMath::Atan2(MovementDirection.Y, MovementDirection.X) - FMath::Atan2(CharacterDirection.Y, CharacterDirection.X);

		/* Normalize StrafingRotation to the range (-PI, PI)*/
		//SET StrafingRotation to the return value of FMath::UnwindRadians(StrafingRotation)
		StrafingRotation = FMath::UnwindRadians(StrafingRotation);

		/* Convert StrafingRotation to degrees and set it in the AnimationInstance*/
		//SET AnimationInstance->StrafingRotation to the value of  FMath::RadiansToDegrees(StrafingRotation)
		AnimationInstance->StrafingRotation = FMath::RadiansToDegrees(StrafingRotation);
		
	}
}

//TODO Lab3:
void ACharacterBase::MoveVertical(float Scale)
{
	
	Move(FVector(1.0f, 0.0f, 0.0f), Scale);
}
//TODO Lab3:
void ACharacterBase::MoveHorizontal(float Scale)
{
	Move(FVector(0.0f, 1.0f, 0.0f), Scale);
}

//TODO Lab3:
void ACharacterBase::Move(FVector Direction, float Scale)
{
	AddMovementInput(Direction, Scale);
}
/*
 Fire() will handle firing the Weapon, by Pulling and releasing the trigger on the current weapon
*/
void ACharacterBase::Fire(bool Toggle)
{
	//TODO Lab3 ACharacterBase::Fire(...):
    //IF CurrentWeapon is valid (Don't use IsValid())
	if(CurrentWeapon)
	{
        //IF Toggle is true
		if(Toggle)
		{
            //CALL PullTrigger() on the CurrentWeapon
			CurrentWeapon->PullTrigger();
	
		}
        //ELSE
		else
		{
            //CALL ReleaseTrigger() on the CurrentWeapon
			CurrentWeapon->ReleaseTrigger();
			
		}
        //ENDIF
		
        //SET bIsFiring to Toggle
		bIsFiring = Toggle;
		
	}
    //END
}

void ACharacterBase::Aim(bool Toggle)
{
	//TODO Lab3 ACharacterBase::Aim(...):
    //SET bIsAiming to Toggle
	bIsAiming = Toggle;
	
}

/*
Interact() Handles interacting with Items. In our case Weapons. We first Drop a weapon (If we have one) then Hold the one that is picked up.
This function is called by InteractPressed() in the APlayerControllerDefault class
*/
void ACharacterBase::Interact(AActor* Actor)
{
	//TODO Lab3 ACharacterBase::Interact(....):
	/* Drop the current weapon.*/
    //CALL DropWeapon()
	DropWeapon();

	AnimationInstance = Cast<UCharacterBaseAnimation>(SkeletalMesh->GetAnimInstance());
	

	/* Check if the actor is an item.*/
    //DECLARE a variable of type AItemBase* called Item and assign it to the Cast of Actor passed into this function. Cast Actor as a AItemBase
	AItemBase* Item = Cast<AItemBase>(Actor);


	//UNCOMMENT
	if(Item == nullptr)
		return;

	/* Check distance from the object.*/
    //DECLARE a float called Distance and SET it to the return value of Item->GetDistanceTo(this)
	float Distance = Item->GetDistanceTo(this);
	

    //IF the Distance is greater than MaxPickUpDistance
        //RETURN

	if (Distance > MaxPickUpDistance) {
		return;
	}
	

	/* Hold the item if it's a weapon.*/
    //DECLARE a AWeaponBase* called Weapon SET it to the Cast of the Item to AWeaponBase. Cast Item to AWeaponBase
	AWeaponBase* Weapon = Cast<AWeaponBase>(Item);
	

    //IF Weapon is valid (Don't use IsValid()
	if(Weapon)
	
	{
        //CALL HoldWeapon() and pass in the Weapon
		HoldWeapon(Weapon);
	
	}
    //ENDIF
}

/*
HoldWeapon() will attach the weapon that is picked up by the Character
*/
void ACharacterBase::HoldWeapon(AWeaponBase* Weapon)
{
	check(Weapon != nullptr && "Passed a null weapon!");
	//TODO Lab3 ACharacterBase::HoldWeapon(...):
	/* Drop currently carried weapon first.*/
    //CALL DropWeapon()

	DropWeapon();

	/* Attach weapon to the character.*/
    //SET CurrentWeapon to weapon
	CurrentWeapon = Weapon;
	
    //CALL Attach() on the CurrentWeapon and pass in this
	CurrentWeapon->Attach(this);

    //CALL Clear() on the CurrentWeapon's OnWeaponFired event

    
	/* Subscribe to weapon's events.*/
    //SUBSCRIBE to the CurrentWeapon's OnWeaponFired and pass in (this, &ACharacterBase::OnWeaponFired)
	
}
/*
DropWeapon() will detach the Weapon Currently held by the character
*/
void ACharacterBase::DropWeapon()
{
	//TODO Lab3 ACharacterBase::DropWeapon(...):
    //IF CurrentWeapon is not null
	
	{
		/* Unsubscribe from weapon's events.*/
        //CALL RemoveDynamic(this, &ACharacterBase::OnWeaponFired) on the CurrentWeapon's OnWeaponFired event
	

		/* Detach weapon from the character.*/
        //CALL Detach() on the CurrentWeapon()
	
        //SET CurrentWeapon to null
	

		/* Reset weapon states states.*/
        //SET bIsFiring to false
	
        //SET bIsAiming to false
	
	}
    //ENDIF
}



/*
OnWeaponFired() is a callback function that is triggered by the Weapon. Here we simply play the animation if we are aiming or not
*/
//Weapon Fired Event Handler
void ACharacterBase::OnWeaponFired()
{
	//TODO Lab3 ACharacterBase::OnWeaponFired():
    /* Play recoil animation depending on the stance.*/
    //IF bIsAiming is true
	
	{
        /*Play the Fire Aim Animation*/
        //CALL Montage_Play(FireAimAnimation) on the AnimationInstance
	
	}
    //ELSE
	//else
	{
        /*Play the Fire Hip Animation*/
        //CALL Montage_Play(FireHipAnimation) on the AnimationInstance
		
	}
    //ENDIF
}

/*
OnDeath() is a callback function that is triggered by the Health Component. Here we Drop the Weapon and do a ragdoll
*/
//Weapon Fired Event Handler
void ACharacterBase::OnDeath()
{
//	check(Health->IsDead() && "Called OnDeath() while alive!");

//TODO Lab3 ACharacterBase::OnDeath():
	/* Stop ticking while dead.*/
    //SET PrimaryActorTick.bCanEverTick to false
	

	/* Drop held weapon.*/
    //CALL DropWeapon
	

	/* Disable character's capsule collision.*/
	

	// Uncomment this code if you want to Allow character's ragdoll to be pushed around. 
	
    /*
	SkeletalMesh->SetCollisionProfileName(TEXT("BlockAll"));
	SkeletalMesh->CanCharacterStepUpOn = ECB_No;
	SkeletalMesh->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	*/

	/* Simulate character's ragdoll.*/
    //CALL SetCollisionEnabled() on the SkeletalMesh and pass in ECollisionEnabled::QueryAndPhysics
	
    //CALL SetSimulatePhysics() on the SkeletalMesh and pass in true
	
}

void ACharacterBase::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	//TODO Lab3 ACharacterBase::OnTakeDamage(...):
	/* Adjust the current health of the actor by subtracting the damage received. The new health value is clamped to ensure it
	 remains within the valid range between 0 and the maximum health. This prevents the health from going below 0 or above the maximum health,
	 which would be nonsensical in the context of a game.*/
	//SET CurrentHealth, Clamp it to X: CurrentHealth - Damage, Min: 0.0f, Max: MaximumHealth using FMath::Clamp()
	

	/* Check if the current health has dropped to 0 or below, which would indicate the actor has been defeated or killed.*/
	if (CurrentHealth <= 0.0f)
	{
		/* This is the point where the actor's death is handled. The OnDeath() function is called to execute any logic associated with
		 the actor's death, such as playing a death animation, removing the actor from the game world, or triggering a game event.*/
		//CALL OnDeath()
		
	}


}

AWeaponBase* ACharacterBase::GetCurrentWeapon()
{
	return CurrentWeapon;
}

class USkeletalMeshComponent* ACharacterBase::GetSkeletalMesh()
{
	return SkeletalMesh;
}
