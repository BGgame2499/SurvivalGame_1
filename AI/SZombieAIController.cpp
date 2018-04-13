// Fill out your copyright notice in the Description page of Project Settings.

#include "SZombieAIController.h"
#include "Engine.h"


ASZombieAIController::ASZombieAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASZombieAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerLocation = GetTargetLocation();
}
void ASZombieAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->GetFirstPlayerController()->GetPawn())
	{

		PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();		//��ȡ��ҵ�ǰ��λ��
	}
		
}


void ASZombieAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

}
