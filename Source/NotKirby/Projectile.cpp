// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");


	//Mesh
	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemStaticMesh"));
	
	ItemStaticMesh->SetupAttachment(Root);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	ItemStaticMesh->SetStaticMesh(SphereVisualAsset.Object);
	ItemStaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ItemStaticMesh->SetWorldScale3D(FVector(0.5f));
	ItemStaticMesh->SetSimulatePhysics(true);
	ItemStaticMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	//Mesh material
	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Game/Materials/M_Magma.M_Magma"));
	ItemStaticMesh->SetMaterial(0, FoundMaterial.Object);

	//Hitbox
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereComponent->SetupAttachment(ItemStaticMesh);
	SphereComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 25.0f));

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginOverlap);
	

	//Life until despawn
	life = 3.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	life -= DeltaTime;

	//Destroy when out of time/life
	if (life <= 0.0f)
	{
		Destroy();
	}
}

void AProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

	ABlock* block = Cast<ABlock>(OtherActor);
	if (block != nullptr)
	{

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Collision with block!"));
		block->Destroy();
	}
}

void AProjectile::setVel(FVector newForce)
{

	ItemStaticMesh->AddForce(newForce);

}

void AProjectile::launch(FVector newForce)
{

	ItemStaticMesh->AddImpulse(newForce);

}
