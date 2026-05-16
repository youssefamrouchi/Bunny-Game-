// Fill out your copyright notice in the Description page of Project Settings.


	#include "Egg.h"


	// Sets default values
	AEgg::AEgg()
	{
 		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;
		BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
		RootComponent = StaticMeshComponent;
		BoxComponent->SetupAttachment(StaticMeshComponent);

		EggEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EggEffect"));
		EggEffect->SetupAttachment(BoxComponent);

	}

	// Called when the game starts or when spawned
	void AEgg::BeginPlay()
	{
		Super::BeginPlay();
		EggEffect->Deactivate();
	
	}

	// Called every frame
	void AEgg::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

	}
	void AEgg::NotifyActorBeginOverlap(AActor* OtherActor)
	{
		RecupEgg();
	}
	

