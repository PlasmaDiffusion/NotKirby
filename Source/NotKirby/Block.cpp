// Fill out your copyright notice in the Description page of Project Settings.

#include "Block.h"


// Sets default values
ABlock::ABlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	

	//Mesh
	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemStaticMesh"));

	ItemStaticMesh->SetupAttachment(Root);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	ItemStaticMesh->SetStaticMesh(SphereVisualAsset.Object);
	ItemStaticMesh->SetWorldScale3D(FVector(0.5f));
	ItemStaticMesh->SetSimulatePhysics(false);
	ItemStaticMesh->SetNotifyRigidBodyCollision(true);
	ItemStaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemStaticMesh->SetMobility(EComponentMobility::Stationary);
	ItemStaticMesh->SetEnableGravity(false);

	//Mesh material
	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Game/Materials/M_Yellow.M_Yellow"));
	ItemStaticMesh->SetMaterial(0, FoundMaterial.Object);

	//Hitbox
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(Root);
	BoxComponent->SetMobility(EComponentMobility::Stationary);
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 25.0f));
	BoxComponent->SetEnableGravity(false);
	//BoxComponent->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlock::BeginOverlap);

	Root->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlock::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

