// Fill out your copyright notice in the Description page of Project Settings.

#include "SBaseBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Player/SBaseCharacter.h"
#include "Engine.h"
#include "GameFramework/ProjectileMovementComponent.h"


ASBaseBullet::ASBaseBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	BulletMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	RootComponent = BulletMeshComp;

	BulletShapeComp = CreateDefaultSubobject<USphereComponent>(TEXT("BulletShape"));
	BulletShapeComp->OnComponentBeginOverlap.AddDynamic(this, &ASBaseBullet::OnHit);
	BulletShapeComp->SetupAttachment(BulletMeshComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovementComp->UpdatedComponent = BulletMeshComp;
	ProjectileMovementComp->InitialSpeed = 13000.f;
	ProjectileMovementComp->MaxSpeed = 13000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = true;

	BulletDamage = 70.0f;	//初始化子弹伤害值

}

void ASBaseBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASBaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBaseBullet::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASBaseCharacter * Pawn = Cast<ASBaseCharacter>(OtherActor);
	if (Pawn)
	{
		FPointDamageEvent DmgEvent;
		DmgEvent.Damage = BulletDamage;
		Pawn->TakeDamage(DmgEvent.Damage, DmgEvent, Pawn->GetController(), this);
		if (BulletParticle)
		{
			FVector Vect = GetActorLocation();
			FRotator Rot = GetActorRotation();
			UGameplayStatics::SpawnEmitterAtLocation(this, BulletParticle, Vect, Rot);
		}
	}
	
}

