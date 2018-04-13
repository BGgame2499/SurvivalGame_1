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
		float GetHealth()const;	//获取当前Character血量

	UFUNCTION(BlueprintCallable, Category = "PlayerCondition")
		float GetMaxHealth()const;	//获取初始化时的血量

	UFUNCTION(BlueprintCallable, Category = "PlayerCondition")
		bool IsAlive() const;	//是否存活

	virtual void ToDeath();		//死亡执行函数

	UFUNCTION(BlueprintCallable, Category = "Targeting")
		FRotator GetAimOffsets() const;	//获取当前瞄准位置
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "PlayerCondition")
		float Health;	//血量值
	//接受伤害值
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
};
