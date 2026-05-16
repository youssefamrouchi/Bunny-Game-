// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCaracter.h"

// Sets default values
ABaseEnemyCaracter::ABaseEnemyCaracter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //PV parameter
	Health = 100.0f;
    MaxHealth = 100.0f;
	bIsDead = false;

}

// Called when the game starts or when spawned
void ABaseEnemyCaracter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemyCaracter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemyCaracter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Damage Inteaction

void ABaseEnemyCaracter::InteragirDamage_Implementation(float AmountDamage)
{
    if (Health > 0.0f)
    {
        Health = Health - AmountDamage;
        
        if (Health <= 0.0f)
        {
            Health = 0.0f;
            bIsDead = true;
            Death();
        }
    }

}





