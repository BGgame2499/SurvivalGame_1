// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Sound/SoundCue.h"
#include "SWeapon.generated.h"

UENUM()
enum class EWeaponState	//武器状态
{
	Idle,
	Firing,
	Equipping,
	Reloading
};

UCLASS()
class SURVIVALGAME_1_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASWeapon();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "WeaponMesh")
		USkeletalMeshComponent * WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly,Category = "BulletScene")	//武器子弹的槽位
		USceneComponent * BulletScene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletClass")
		TSubclassOf <class ASBaseBullet> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDamage")
		float WeaponDamage;		//武器伤害值

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletBox")
		int32 BulletBoxMaxNum;		//单个弹夹子弹容量

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FiringSpeed")
		float FiringSpeed;		//武器开火速度


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem * FireParticle;		//开火特效

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireSound")
		USoundCue * FireSound;		//开火音效

public:
	UFUNCTION(BlueprintCallable, Category = "OnFire")
		void OnFire();	//开火

	UFUNCTION(BlueprintCallable, Category = "EndFire")
		void EndFire();	//停火

	UFUNCTION(BlueprintCallable, Category = "GetBulletCurrentNum")
		int32 GetBulletCurrentNum() const;	//获取当前子弹数量

private:
	int32 BulletCurrentNum;

	EWeaponState CurrentWeaponState;	//当前武器状态

	FTimerHandle mTimerHandle;

public:	
	virtual void Tick(float DeltaTime) override;

	void CreateBullet();
	
	
};
