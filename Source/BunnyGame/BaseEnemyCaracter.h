// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include"Components/SkeletalMeshComponent.h"
#include "HpInterface.h"

#include "BaseEnemyCaracter.generated.h"

UCLASS()
class BUNNYGAME_API ABaseEnemyCaracter : public ACharacter, public IHpInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemyCaracter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	// Variables pour les components de abse
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTreeAsset;
	


protected:

	//PV 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bIsDead = false;

	//Intterface HP


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Health")
	void Death();

	virtual void InteragirDamage_Implementation(float AmountDamage);

	
};
