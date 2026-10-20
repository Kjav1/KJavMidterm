// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Components/SphereComponent.h"
#include "BaseBullet.h"
#include "Engine/EngineBaseTypes.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//This will crash if not in Constructor (I was putting it in BeginPlay())
	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Location")); //Troubleshooting determined this line of code (when in Begin Play) was causing the crash	
	//moving it into constructor seems to fix it!
	SpawnLocation->SetupAttachment(GetRootComponent());
	

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CanShoot = true;

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//UE_LOG(LogTemp, Warning, TEXT("Component Location: %s"), *MySceneComponent->GetComponentLocation().ToString());

//	UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *SpawnLocation->GetComponentLocation().ToString());
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::GetHurt(int Damage)
{
	//get hurt
	Health -= Damage; 
}

void ABaseCharacter::Shoot() 
{
	//move shooting conditions to over here!

	if (CanShoot) 
	{

		//shooting 
		FActorSpawnParameters SpawnParams; 
		SpawnParams.Instigator = this; //who made this actor, useful for tracking bullets / points

		AActor* SpawnedBullet = GetWorld()->SpawnActor<ABaseBullet>(
			BulletClass, 
			SpawnLocation->GetComponentLocation(), 
			GetActorRotation(),
			SpawnParams
		);

		// if (SpawnedBullet) //used this to troubleshoot when actors weren't showing up in outline - Setting needed to be changed to 'update in PIE' to be visible
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("Hello World"));
		// }

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Shoot!"));


		CanShoot = false; 

		FTimerHandle ShootCooldown; 
        GetWorld()->GetTimerManager().SetTimer(ShootCooldown, this, &ABaseCharacter::SetShoot, CooldownTimer, false);
	}
}

void ABaseCharacter::SetShoot()
{
	CanShoot = true;
}