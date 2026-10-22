// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


ABasePlayerCharacter::ABasePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true; 

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 0.1f; 

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	//Camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePlayerCharacter::GetHurt(int Damage)
{
	Super::GetHurt(Damage);
	if (Health <= 0) 
	{
		FString CurrentLevelName = GetWorld()->GetMapName(); //get name of current level, as a string
		
		// Remove prefix if running in PIE (Play In Editor)
		CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

		//opening the level again, to 'reset it'
		UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName)); 
	}	
}

void ABasePlayerCharacter::Shoot() 
{
	Super::Shoot(); 
}

