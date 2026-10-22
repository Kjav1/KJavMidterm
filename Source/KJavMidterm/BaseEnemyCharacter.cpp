// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemyCharacter.h"


// ABaseEnemyCharacter::ABaseEnemyCharacter()
// {
// 	PrimaryActorTick.bCanEverTick = true;

// }

void ABaseEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABaseEnemyCharacter::Shoot()
{
    Super::Shoot();
}

void ABaseEnemyCharacter::GetHurt(int Damage)
{
    Super::GetHurt(Damage);

    if (Health <= 0)
    {
        Destroy(this);
    }
}

void ABaseEnemyCharacter::SetShoot()
{
    Super::SetShoot();
}
