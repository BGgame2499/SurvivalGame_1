// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Sound/SoundCue.h"
#include "SWeapon.generated.h"

UENUM()
enum class EWeaponState	//����״̬
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

	UPROPERTY(VisibleDefaultsOnly,Category = "BulletScene")	//�����ӵ��Ĳ�λ
		USceneComponent * BulletScene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletClass")
		TSubclassOf <class ASBaseBullet> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDamage")
		float WeaponDamage;		//�����˺�ֵ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletBox")
		int32 BulletBoxMaxNum;		//���������ӵ�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FiringSpeed")
		float FiringSpeed;		//���������ٶ�


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem * FireParticle;		//������Ч

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireSound")
		USoundCue * FireSound;		//������Ч

public:
	UFUNCTION(BlueprintCallable, Category = "OnFire")
		void OnFire();	//����

	UFUNCTION(BlueprintCallable, Category = "EndFire")
		void EndFire();	//ͣ��

	UFUNCTION(BlueprintCallable, Category = "GetBulletCurrentNum")
		int32 GetBulletCurrentNum() const;	//��ȡ��ǰ�ӵ�����

private:
	int32 BulletCurrentNum;

	EWeaponState CurrentWeaponState;	//��ǰ����״̬

	FTimerHandle mTimerHandle;

public:	
	virtual void Tick(float DeltaTime) override;

	void CreateBullet();
	
	
};
