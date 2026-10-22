// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyController.h"
#include "BaseEnemyCharacter.h"

void ABaseEnemyController::BeginPlay()
{
    ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(GetPawn());

    if (Enemy && Enemy->BTAsset)
    {
            RunBehaviorTree(Enemy->BTAsset);
    } 
}