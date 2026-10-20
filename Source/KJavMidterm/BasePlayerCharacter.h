// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BasePlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KJAVMIDTERM_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public: 
	ABasePlayerCharacter();
	
public: 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USpringArmComponent* CameraBoom; 

	UPROPERTY(EditAnywhere)
	float speed;

	virtual void GetHurt(int Damage);

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class UCameraComponent* GetCamera() const {return Camera; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const {return CameraBoom; }

protected: 

	virtual void BeginPlay() override;

	void Shoot(); 

private: 


};