// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SBaseCharacter.h"
#include "SZombieCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_1_API ASZombieCharacter : public ASBaseCharacter
{
	GENERATED_BODY()
public:
	ASZombieCharacter();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HitShape")
		class USphereComponent * HitShapeComp;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
		float Damage;

public:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void BeginPlay() override;
	
	virtual void ToDeath()override;
};
