// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBullet.h"
#include "Components/SphereComponent.h" 
#include "GameFramework/ProjectileMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->SetSimulatePhysics(true);

	SetRootComponent(SphereMesh); //set mesh as root component 

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SphereMeshAsset.Succeeded()) 
	{
		this->SphereMesh->SetStaticMesh(SphereMeshAsset.Object); //adds Mesh if it found the sphere mesh
	}

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision")); //creates collider
	SphereCollision->SetupAttachment(SphereMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->ProjectileGravityScale = 0; //will not fall down
	ProjectileMovement->InitialSpeed = BulletSpeed;
	ProjectileMovement->MaxSpeed = BulletSpeed;
}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();

	//for understanding collisions
	SphereMesh->OnComponentHit.AddDynamic(this, &ABaseBullet::OnComponentHit); //needs to be in beginplay()

	//timer to destroy bullet after a certain amount of time, to reduce amount of actors in a scene at a given time
	FTimerHandle TimerHandle; 

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseBullet::DestroyBullet, DespawnTimer, false);
	
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBullet::DestroyBullet() //another troubleshooting reminder that functions must be relative to the script (As in, ABaseBullet::DestroyBullet() and not DestroyBullet())
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Destroy Object!!!")); //testing function
	this->Destroy(); //destroys actor
}

void ABaseBullet::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit!!!")); //testing function
	
	HitCharacter = Cast<ABaseCharacter>(OtherActor); //if what was hit has some sort of character script, then it will get hurt
	if (HitCharacter) 
	{
		HitCharacter->GetHurt(BulletDamage);
	} 

	this->Destroy(); //destroy after hitting something
}


