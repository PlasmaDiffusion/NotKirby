// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
/**
 * 
 */
class NOTKIRBY_API Ability
{
private:

	UCharacterMovementComponent* CharacterMovement;

	bool inputR;
	bool inputL;
	bool inputU;
	bool inputD;

public:
	Ability(UCharacterMovementComponent* CharacterMovemnet);
	~Ability();
};
