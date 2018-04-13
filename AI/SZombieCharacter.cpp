// Fill out your copyright notice in the Description page of Project Settings.

#include "SZombieCharacter.h"
#include "Components/SphereComponent.h"
#include "Player/SCharacter.h"
#include "Engine.h"
#include "SurvivalGame_1GameModeBase.h"


ASZombieCharacter::ASZombieCharacter()
{
	HitShapeComp = CreateDefaultSubobject<USphereComponent>(TEXT("HitShape"));
	HitShapeComp->OnComponentBeginOverlap.AddDynamic(this, &ASZombieCharacter::OnHit);
	HitShapeComp->SetupAttachment(GetRootComponent());

	Damage = 10.0f;
}

void ASZombieCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ASZombieCharacter::ToDeath()	//ÖØÐ´ËÀÍöº¯Êý
{
	ASurvivalGame_1GameModeBase * GameMode = Cast<ASurvivalGame_1GameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->CurrentZombieNum--;
	}
	Destroy();
}

void ASZombieCharacter::OnHit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ASCharacter * Player =  Cast<ASCharacter>(OtherActor);
	if (Player)
	{
		FPointDamageEvent DmgEvent;
		DmgEvent.Damage = Damage;
		Player->TakeDamage(DmgEvent.Damage, DmgEvent, GetController(), this);
	}

}
