// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

UCLASS()
class KJAVMIDTERM_API ABaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBullet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* SphereCollision; 

	class UStaticMeshComponent* SphereMesh;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovement; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletSpeed = 2500.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DespawnTimer = 5.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BulletDamage = 1;


	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	class ABaseCharacter* HitCharacter; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestroyBullet(); 

};
