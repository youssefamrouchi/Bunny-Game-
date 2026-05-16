// Fill out your copyright notice in the Description page of Project Settings.


#include "Claw.h"


// Sets default values
AClaw::AClaw()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Mesh
	ClawMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClawMesh"));
	RootComponent = ClawMesh;


	// niagara effect
	ClawEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ClawVisualEffect"));
	ClawEffect->SetupAttachment(RootComponent);
	
	
		// Projectile component
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovemntComponent"));
	
	MovementComponent->UpdatedComponent = RootComponent;	
	MovementComponent->InitialSpeed = 2000.f;
	MovementComponent->MaxSpeed = 10000.f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AClaw::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AClaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


