// Fill out your copyright notice in the Description page of Project Settings.
#include "CPP_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h" //needed this in order to call UEnhancedInputComponent pointer
#include "EnhancedInputSubsystems.h" 
#include "Components/InputComponent.h"

ACPP_PlayerController::ACPP_PlayerController()
{
    PrimaryActorTick.bCanEverTick = true; 

}

void ACPP_PlayerController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime); 
}


void ACPP_PlayerController::BeginPlay() 
{
    Super::BeginPlay();
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) 
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

}

void ACPP_PlayerController::SetupInputComponent() 
{
    Super::SetupInputComponent(); 

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) 
    {
        //some error here with function at end
        EnhancedInputComponent->BindAction(MovementInput, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Move);

        EnhancedInputComponent->BindAction(LookInput, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Look);
        //NOTE: Video said to use TriggerEvent:Ongoing 
        //That one does not work. For continuous data like walking or looking, use Triggered
    }

}

void ACPP_PlayerController::Look(const FInputActionValue& LookValue) 
{
    FVector2D LookVector = LookValue.Get<FVector2D>(); //2d vector of mouse x and y

    GetPawn()->AddControllerPitchInput(LookVector.Y * Sensitivity); 
    
    GetPawn()->AddControllerYawInput(LookVector.X * Sensitivity);

    //we want pitch and yaw
    //mouse Y is pitch, X is yaw
    //GetPawn()->SetControlRotation(LookVector, )
    
}

void ACPP_PlayerController::Move(const FInputActionValue& Value) 
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    FVector InputVector = FVector(MovementVector, 0); //turn it into a vector3
//look for relative space
    GetPawn()->AddMovementInput(InputVector, Speed, false);
}

