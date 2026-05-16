// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HpInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHpInterface : public UInterface
{
	GENERATED_BODY()
};


/**
 * 
 */
class BUNNYGAME_API IHpInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void InteragirDamage(float AmountDamage);

};
