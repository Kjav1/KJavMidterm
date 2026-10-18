// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"
#include "Components/SphereComponent.h" 

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SetRootComponent(SphereMesh); //set mesh as root component 

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SphereMeshAsset.Succeeded()) 
	{
		this->SphereMesh->SetStaticMesh(SphereMeshAsset.Object); //adds Mesh if it found the sphere mesh
	}

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision")); //creates collider
	SphereCollision->SetupAttachment(SphereMesh);

}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

