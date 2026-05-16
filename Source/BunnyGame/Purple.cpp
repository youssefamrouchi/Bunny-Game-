// Fill out your copyright notice in the Description page of Project Settings.


#include "Purple.h"

// Sets default values
APurple::APurple()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PurpleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PurpleMesh"));
	PurpleMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APurple::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APurple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator NewRotation = FRotator(0.0f, 90.0f * DeltaTime, 0.0f);

	// Applique la rotation relative
	AddActorLocalRotation(NewRotation);

}

