// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Claw.generated.h"

UCLASS()
class BUNNYGAME_API AClaw : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClaw();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent* ClawMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* MovementComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX")
	UNiagaraComponent* ClawEffect;


};
