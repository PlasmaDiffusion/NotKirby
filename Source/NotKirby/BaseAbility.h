// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "BaseAbility.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOTKIRBY_API UBaseAbility : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UBaseAbility();

	void attack(UCharacterMovementComponent* movement);

	void setInputs(bool inputR, bool inputL, bool inputU, bool inputD);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Direction for attack input
	bool inputR;
	bool inputL;
	bool inputU;
	bool inputD;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Item Config")
	class UStaticMeshComponent* ItemStaticMesh;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
