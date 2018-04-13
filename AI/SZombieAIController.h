// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "SZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_1_API ASZombieAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASZombieAIController();

	virtual void BeginPlay()override;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerLocation")
		FVector PlayerLocation;


public:
	virtual void Possess(class APawn* InPawn)override;
	virtual void Tick(float DeltaTime) override;
	
};
