// Fill out your copyright notice in the Description page of Project Settings.


#include "EnnemiAIController.h"

#include "BaseEnemyCaracter.h"

void AEnnemiAIController::BeginPlay()
{
	ABaseEnemyCaracter* EnemyCaracter = Cast<ABaseEnemyCaracter>(GetPawn());
	if (EnemyCaracter && EnemyCaracter->BehaviorTreeAsset)
	{
		// Initialisation ou configuration spécifique pour EnemyCharacter
		RunBehaviorTree (EnemyCaracter->BehaviorTreeAsset);
	}
}



