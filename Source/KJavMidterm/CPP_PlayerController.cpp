// Fill out your copyright notice in the Description page of Project Settings.
#include "CPP_PlayerController.h"
#include "BaseCharacter.h" //required to access script functions (shoot())
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
        Subsystem->AddMappingContext(DefaultMappingContext, 0); //needed to establish mapping context
    }

    PlayerCharacter = Cast<ABaseCharacter>(GetPawn()); //accessing BaseCharacter script from Player Character, requires #include BaseCharacter

}

void ACPP_PlayerController::SetupInputComponent() 
{
    Super::SetupInputComponent(); 

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) 
    {
        //some error here with function at end
        EnhancedInputComponent->BindAction(MovementInput, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Move);

        EnhancedInputComponent->BindAction(LookInput, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Look);
        
        EnhancedInputComponent->BindAction(ShootInput, ETriggerEvent::Started, this, &ACPP_PlayerController::PlayerShoot);
        
        //NOTE: Video said to use TriggerEvent:Ongoing 
        //That one does not work. For continuous data like walking or looking, use Triggered
    }

}

void ACPP_PlayerController::PlayerShoot() 
{
    if (PlayerCharacter) //if script exists, then use it to shoot
    {
        PlayerCharacter->Shoot();
    }

    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Shoot!"));	//handy dandy debug tool :)
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
    FRotator pawnRotation = GetPawn()->GetControlRotation();  //grabbing player rotation

    //used Medium article mentioned in Document - This gets the relative directions/rotations based on the rotation you gave it
    const FVector ForwardDirection = FRotationMatrix(pawnRotation).GetUnitAxis(EAxis::X); //Grabbing Rotational Directions
    const FVector RightDirection = FRotationMatrix(pawnRotation).GetUnitAxis(EAxis::Y);


    GetPawn()->AddMovementInput(ForwardDirection, MovementVector.X*Speed); //relative to forward/right direction, change this value
    GetPawn()->AddMovementInput(RightDirection, MovementVector.Y*Speed);

//    GetPawn()->AddMovementInput(InputVector, Speed, false); //used before, had no relative movement (moved in world space, not where player faced)
}

