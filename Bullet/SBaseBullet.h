// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseBullet.generated.h"

UCLASS()
class SURVIVALGAME_1_API ASBaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBaseBullet();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "BulletMesh")
		class UStaticMeshComponent * BulletMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BulletSphere")
		class USphereComponent * BulletShapeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem * BulletParticle;

	float BulletDamage;
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
