// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class NOTKIRBY_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Item Config")
		class USceneComponent* Root;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Item Config")
		class UStaticMeshComponent* ItemStaticMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Item Config")
		class UBoxComponent* BoxComponent;

	// Overlap
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
