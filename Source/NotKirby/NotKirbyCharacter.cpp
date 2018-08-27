// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "NotKirbyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ANotKirbyCharacter::ANotKirbyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 1.00f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	inputR = false;
	inputL = false;
	inputU = false;
	inputD = false;

	ability = CreateDefaultSubobject<UBaseAbility>(FName("Ability"));
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void ANotKirbyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//PrimaryActorTick.bCanEverTick = true; //We won't be ticked by default  


	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANotKirbyCharacter::MoveRight);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ANotKirbyCharacter::attack);

	PlayerInputComponent->BindAxis("MoveUp", this, &ANotKirbyCharacter::inputUp);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ANotKirbyCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ANotKirbyCharacter::TouchStopped);
}

void ANotKirbyCharacter::MoveRight(float Value)
{


	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);

	//Attack direction vars
	if (Value > 0.1f) inputR = true;
	else if (Value < -0.1f) inputL = true;
	else
	{
		inputR = false;
		inputL = false;
	}
}

void ANotKirbyCharacter::inputUp(float Value)
{
	//Enter door or whatever here


	//Attack direction vars
	if (Value > 0.1f) inputU = true;
	else if (Value < -0.1f) inputD = true;
	else
	{
		inputU = false;
		inputD = false;
	}
}


void ANotKirbyCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ANotKirbyCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ANotKirbyCharacter::attack()
{
	FVector sideForce(0.0f, -100000.0f, 0.0f);



	//Multiple combos
	if (inputR && inputU)
	{
		//if (GEngine)
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Attacking upright!"));
	}
	else if (inputR && inputD)
	{

	}

	//Single combos
	else if (inputR) //Right attack
	{
	


		GetCharacterMovement()->AddImpulse(sideForce);
	}
	else if (inputL) //Left Attack
	{
		GetCharacterMovement()->AddImpulse(-sideForce);
	}
	else if (inputU) //Attack up
	{
		//Init some values
		FVector location(0.0f, 25.0f, 20.0f);
		FRotator rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters spawnInfo;
		FVector forceL(0.0f, -20000.0f, 10000.0f);
		FVector forceR(0.0f, 20000.0f, 10000.0f);

		//Spawn projectile and add an impulse
		AProjectile *proj = GetWorld()->SpawnActor<AProjectile>(GetActorLocation() + location, rotation, spawnInfo);
		proj->launch(forceR);

		proj = GetWorld()->SpawnActor<AProjectile>(GetActorLocation() - location, rotation, spawnInfo);
		proj->launch(forceL);
	}
	else if (inputD) //Attack down
	{
		//Init some values
		FVector location(0.0f, 25.0f, 20.0f);
		FRotator rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters spawnInfo;
		FVector forceL(0.0f, 0.0f, 5000.0f);
		FVector forceR(0.0f, 0.0f, 5000.0f);

		//Spawn projectile and add an impulse
		AProjectile *proj = GetWorld()->SpawnActor<AProjectile>(GetActorLocation() + location, rotation, spawnInfo);
		proj->launch(forceR);

		proj = GetWorld()->SpawnActor<AProjectile>(GetActorLocation() - location, rotation, spawnInfo);
		proj->launch(forceL);
	}
	else //Default attack: Basic projectile
	{
		//Determine where player is facing
		FRotator playerRotation = GetActorRotation();

		//Init some values
		FVector location(0.0f, 5.0f, 0.0f);
		FRotator rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters spawnInfo;
		FVector force(0.0f, -100000.0f, 0.0f);

		//Change stuff if facing left
		if (playerRotation.Yaw < 0.0f)
		{
			location = -location;
			force = -force;
		}

		//Spawn projectile and add an impulse
		AProjectile *proj = GetWorld()->SpawnActor<AProjectile>(GetActorLocation() + location, rotation, spawnInfo);
		proj->launch(force);
	}
}



/*void ANotKirbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call parent class tick function  

	if (bIsMoving == true)
	{
		UpdateOffset(DeltaTime);
	}

}*/