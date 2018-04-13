// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "SCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_1_API ASCharacter : public ASBaseCharacter
{
	GENERATED_BODY()
private:
	ASCharacter();

	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
		USpringArmComponent * CameraBoomComp;

	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent * CameraComp;

	UPROPERTY(EditAnywhere, Category = "WeaponScene")	//�������ɵĲ�λ
		USceneComponent * WeaponScene_1;

	bool isFire;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponClass")	//Ҫ���ɵ�������
		TSubclassOf <class ASWeapon> WeaponClass;

	ASWeapon * CurrentWeapon;	//��ǰ����������ָ��
public:
	UFUNCTION(BlueprintCallable, Category = "isFire")
		bool GetIsFire();	//�����Ƿ񿪻�


public:
	virtual void MoveForward(float Val);
	virtual void MoveRight(float Val);

	void OnStartFire();
	void OnStopFire();
};
