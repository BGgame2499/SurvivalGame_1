// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalGame_1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_1_API ASurvivalGame_1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASurvivalGame_1GameModeBase();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurrentPlayerPawn")
		class ASCharacter * CurrentPlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurentZombieClass")
		TSubclassOf<class ASZombieCharacter> CurentZombieClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurentZombieClass")
		TSubclassOf<class ASZombieCharacter> CurentZombieClass_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurrentTime")	//当前存活时间
		int32 CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxZombieNum")	//最大生成僵尸数量
		int32 MaxZombieNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurrentZombieNum")	//当前存活僵尸数量
		int32 CurrentZombieNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurrentWave")	//当前波数
		int32 Wave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurrentZombieLocation")	//创建僵尸的各个位置
		TArray<FTransform> CurrentZombieLocation;
private:
	virtual void BeginPlay()override;


	FTimerHandle mTimerHandle;

public:
	virtual void Tick(float DeltaTime)override;
	
	UFUNCTION()
		void Timeing();

	UFUNCTION(BlueprintCallable, Category = "CurentZombie")
		void CurentZombie(int32 CurentZombieNum);
};
