// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"

Ability::Ability(UCharacterMovementComponent* CharacterMovement)
{
	this->CharacterMovement = CharacterMovement;

	inputR = false;
	inputL = false;
	inputU = false;
	inputD = false;
}

Ability::~Ability()
{
}
