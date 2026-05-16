// Fill out your copyright notice in the Description page of	 Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


//Components 
#include"Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
//Other
#include "Blueprint/UserWidget.h"
#include"InputActionValue.h"
//Interface 
#include "HpInterface.h"
#include "InteractInterface.h"


#include "BP_Bunny.generated.h"

UCLASS(Blueprintable,BlueprintType)
class BUNNYGAME_API ABP_Bunny : public ACharacter, public IHpInterface, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABP_Bunny();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* Camera;

	// Méthode Interface
	
private:
	// Inpput functions
	void MoveLR(const FInputActionValue& Value);
	void MoveFB(const FInputActionValue& Value);
	void LookAround(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void StartAim(const FInputActionValue& Value);
	void StopAim(const FInputActionValue& Value);
	void SpawnPurple(const FInputActionValue& Value);
	// Attack Fonction
	
protected:

	//Input Actions and Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditANywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* INP_Move_LR;
	UPROPERTY(EditANywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* INP_Move_FB;
	UPROPERTY(EditANywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* INP_Sprint;
	UPROPERTY(EditANywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* INP_LookAround;
	UPROPERTY(EditANywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* INP_Attack;
	UPROPERTY(EditANywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* INP_Aim;
	UPROPERTY(EditANywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* INP_ATT_Purple;

	UPROPERTY(EditANywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* INP_Interact;


	// Variable for Claw
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Claw")
	TSubclassOf<AActor> PawnToSpawn;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool BCanSprint;

	// Variable AIm

	FVector LocInitCam;

	FVector LocAimCam;

	UPROPERTY(EditAnywhere, Category = "Camera Settings")
	float AimSensitivity = 0.04f;


	UPROPERTY(EditAnywhere, Category = "Camera Settings")
	float DefaultSensitivity = 1.0f;
	UPROPERTY()

	float CurrentSensitivityMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	UArrowComponent* ClawArrow;


	// UI For Claw
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Claw")
	TSubclassOf<UUserWidget> ClawWidgetClass;
	UPROPERTY()
	UUserWidget* CrosshairInstance;
	// Cinematic 
	UFUNCTION(BlueprintImplementableEvent, Category = "Cinematics")
	void PlayMyCinematic();

	//PV 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bIsDead = false;

	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void Death();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate")
	float UltimateCharge = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate")
	float MaxUltimateCharge = 100.0f;


	// Unreal Interface

	virtual void InteragirDamage_Implementation(float AmountDamage);

	virtual void InteragirEggToMain(uint8 Amount_Egg);

	

	UFUNCTION()
	void InteragirObject();

	// Othes Variables
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	uint8 AmountMiniEgg = 0;

};	
