// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KJAVMIDTERM_API ABaseEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
	ABaseEnemyCharacter();
	
	public:
virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BTAsset;

	void Shoot(); //for player controller to access

	virtual void GetHurt(int Damage) override;  //no need to put override if this is the first instsance of a method (children will write 'override' but the parent will not)


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool CanShoot;

	void SetShoot();


private:	

};
