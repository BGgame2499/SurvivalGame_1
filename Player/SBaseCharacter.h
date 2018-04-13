// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SBaseCharacter.generated.h"

UCLASS(ABSTRACT)
class SURVIVALGAME_1_API ASBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASBaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "PlayerCondition")
		float GetHealth()const;	//��ȡ��ǰCharacterѪ��

	UFUNCTION(BlueprintCallable, Category = "PlayerCondition")
		float GetMaxHealth()const;	//��ȡ��ʼ��ʱ��Ѫ��

	UFUNCTION(BlueprintCallable, Category = "PlayerCondition")
		bool IsAlive() const;	//�Ƿ���

	virtual void ToDeath();		//����ִ�к���

	UFUNCTION(BlueprintCallable, Category = "Targeting")
		FRotator GetAimOffsets() const;	//��ȡ��ǰ��׼λ��
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "PlayerCondition")
		float Health;	//Ѫ��ֵ
	//�����˺�ֵ
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
};
