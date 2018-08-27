// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAbility.h"


// Sets default values for this component's properties
UBaseAbility::UBaseAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemStaticMesh"));

	// This is Component Specific. Just wanted to show you that you can access it here too.
	//ItemStaticMesh->bReceivesDecals = false;
	//ItemStaticMesh->bCastDynamicShadow = true;
	//ItemStaticMesh->SetOnlyOwnerSee(false);
	//ItemStaticMesh->SetOwnerNoSee(false);
	// ...
}

void UBaseAbility::attack(UCharacterMovementComponent* movement)
{

}

void UBaseAbility::setInputs(bool inputR, bool inputL, bool inputU, bool inputD)
{
	this->inputR = inputR;
	this->inputL = inputL;
	this->inputU = inputU;
	this->inputD = inputD;
}


// Called when the game starts
void UBaseAbility::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

