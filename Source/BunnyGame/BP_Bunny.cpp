// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Bunny.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
// Sets default values
ABP_Bunny::ABP_Bunny()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //Camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(GetRootComponent());
    Camera->SetRelativeLocation(FVector(-360.0f,0.0f,60.0f));
	LocInitCam = Camera->GetRelativeLocation();
	LocAimCam = FVector(-220.0f, 80.0f, 60.0f);

    // Aim parameter
    CurrentSensitivityMultiplier = DefaultSensitivity;
    AimSensitivity = 0.3f; 
    DefaultSensitivity = 1.0f;

	// Claw parameter
	ClawArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ClawArrow"));
    ClawArrow->SetupAttachment(Camera);

    //Pv Parameter
	Health = 100.0f;
	MaxHealth = 100.0f;
    bIsDead = false;

    //Other
    AmountMiniEgg = 0;
}   

// Called when the game starts or when spawned
void ABP_Bunny::BeginPlay()
{
	Super::BeginPlay();
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        // 2. On récupère le "Subsystem" qui gère les inputs améliorés
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            // 3. On ajoute ton Mapping Context (si la variable n'est pas vide)
            if (DefaultMappingContext)
            {
                // La priorité est 0 (par défaut)
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }
    }
	
}

// Called every frame
void ABP_Bunny::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABP_Bunny::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // On lie l'action de mouvement horizontal à la méthode de déplacement
        if (INP_Move_LR)
        {
            EnhancedInputComponent->BindAction(INP_Move_LR, ETriggerEvent::Triggered, this, &ABP_Bunny::MoveLR);
        }
        if (INP_Move_FB)
        {
            EnhancedInputComponent->BindAction(INP_Move_FB, ETriggerEvent::Triggered, this, &ABP_Bunny::MoveFB);
        }
        if (INP_LookAround)
        {
            EnhancedInputComponent->BindAction(INP_LookAround, ETriggerEvent::Triggered, this, &ABP_Bunny::LookAround);
		}
        if (INP_Sprint)
        {
            EnhancedInputComponent->BindAction(INP_Sprint, ETriggerEvent::Triggered, this, &ABP_Bunny::Sprint);
            EnhancedInputComponent->BindAction(INP_Sprint, ETriggerEvent::Completed, this, &ABP_Bunny::Sprint);
        }
        if (INP_Attack) 
        {
            EnhancedInputComponent->BindAction(INP_Attack, ETriggerEvent::Started, this, &ABP_Bunny::Attack);
        }
        if (INP_Aim)
        {
            EnhancedInputComponent->BindAction(INP_Aim, ETriggerEvent::Started, this, &ABP_Bunny::StartAim);
			EnhancedInputComponent->BindAction(INP_Aim, ETriggerEvent::Completed, this, &ABP_Bunny::StopAim);
		}
        if (INP_ATT_Purple)
        {
            EnhancedInputComponent->BindAction(INP_ATT_Purple, ETriggerEvent::Triggered, this, &ABP_Bunny::SpawnPurple);
		}
        if (INP_Interact)
        {
            EnhancedInputComponent->BindAction(INP_Interact, ETriggerEvent::Started, this, &ABP_Bunny::InteragirObject);
		}

    }

}

// Input functions
void ABP_Bunny::MoveLR(const FInputActionValue& Value)
{
    BCanSprint = false;
    float MoveValue = Value.Get<float>();
    AddMovementInput(GetActorRightVector(), MoveValue);
}
void ABP_Bunny::MoveFB(const FInputActionValue& Value)
{
    float MoveValue = Value.Get<float>();
    AddMovementInput(GetActorForwardVector(), MoveValue);
    if (MoveValue == 1.0f)
    {
		BCanSprint = true;
    }
    else {
		BCanSprint = false;
    }
}
void ABP_Bunny::LookAround(const FInputActionValue& Value)
{
    FVector2D LookValue = Value.Get<FVector2D>();
    AddControllerYawInput(LookValue.X * CurrentSensitivityMultiplier);
    AddControllerPitchInput(LookValue.Y * CurrentSensitivityMultiplier);
}
void ABP_Bunny::Sprint(const FInputActionValue& Value)
{
	bool bIsSprinting = Value.Get<bool>();
    if (bIsSprinting)
    {
        if (BCanSprint)
        {
            GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
        }
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}
void ABP_Bunny::StopSprint(const FInputActionValue& Value)
{
    bool bIsSprinting = Value.Get<bool>();
    if (!bIsSprinting)
    {
        GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    }
}

// Attack function
void ABP_Bunny::Attack(const FInputActionValue& Value) 
{
  if (PawnToSpawn)
    {
	    

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();
		FVector SpawnLocation = ClawArrow->GetComponentLocation();
		FRotator SpawnRotation = ClawArrow->GetComponentRotation();
        
        GetWorld()->SpawnActor<AActor>(PawnToSpawn,SpawnLocation,SpawnRotation, SpawnParams);
  }

}   
void ABP_Bunny::StartAim(const FInputActionValue& Value)
{
    bool bIsAiming = Value.Get<bool>();
    if (bIsAiming)
    {
        Camera->SetRelativeLocation(LocAimCam);
        CurrentSensitivityMultiplier = AimSensitivity;
		if (ClawWidgetClass)
        {
            CrosshairInstance = CreateWidget<UUserWidget>(GetWorld(), ClawWidgetClass);
            if (CrosshairInstance)
            {
                CrosshairInstance->AddToViewport();
            }
        }
        
    }
    else
    {
        Camera->SetRelativeLocation(LocInitCam);
    }
}
void::ABP_Bunny::StopAim(const FInputActionValue& Value)
{
    bool bIsAiming = Value.Get<bool>();
    if (!bIsAiming)
    {
        Camera->SetRelativeLocation(LocInitCam);
        CurrentSensitivityMultiplier = DefaultSensitivity;
        if (CrosshairInstance)
        {
            CrosshairInstance->RemoveFromParent();
            CrosshairInstance = nullptr;
		}
    }
}

// Purple
void ABP_Bunny::SpawnPurple(const FInputActionValue& Value)
{
    PlayMyCinematic();
}

// Damage Inteaction

void ABP_Bunny::InteragirDamage_Implementation(float AmountDamage)
{
    if (Health >0.0f)
    {
		
        Health = Health -   AmountDamage;
		if (Health <= 0.0f)
        {
            Health = 0.0f;
            bIsDead = true;
			Death();
        }
    }

}

//Interagir Interface

void    ABP_Bunny::InteragirObject()
{
  
        // 1. Définir la zone de départ et de fin 
        FVector Start = GetActorLocation();
        FVector End = Start + (GetActorForwardVector() * 100.0f); // Légèrement devant

        // 2. Paramètres de la forme (Sphère)
        FCollisionShape MaSphere = FCollisionShape::MakeSphere(300.0f);

      
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this);

        FHitResult Hit;

        bool bAHit = GetWorld()->SweepSingleByChannel(
            Hit,
            Start,
            End,
            FQuat::Identity,
            ECC_Visibility, 
            MaSphere,
            Params
        );

        
        if (bAHit && Hit.GetActor())
        {
            AActor* Cible = Hit.GetActor();

            if (Cible->Implements<UInteractInterface>())
            {
                // On appelle la fonction de l'interface v
                
                IInteractInterface::Execute_Interagir(Cible);
		
            }
        }
    
}

// Amount Egg Update
void ABP_Bunny::InteragirEggToMain(uint8 Amount_Egg)
{
    AmountMiniEgg = AmountMiniEgg + Amount_Egg;
}


