// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "InputActionValue.h"
#include "CPP_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputAction;

/**
 * 
 */
UCLASS()
class KJAVMIDTERM_API ACPP_PlayerController : public APlayerController
{
	
	GENERATED_BODY()
	
	public: 
	ACPP_PlayerController(); 

	public: 
	UPROPERTY(EditAnywhere, BlueprintReadOnly) //public variable, speed of movement
	float Speed; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly) //public variable, speed of rotation
	float Sensitivity; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MovementInput; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* LookInput; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* ShootInput; 

	protected: 

	virtual void SetupInputComponent() override; 

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	void Look(const FInputActionValue& LookValue); 

	void PlayerShoot();

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value); //CONST FINPUTACTIONVALUE is needed, not FInputAction
	
	class ABaseCharacter* PlayerCharacter;

	private: 


};
