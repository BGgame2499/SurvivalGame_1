// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivalGame_1GameModeBase.h"
#include "Engine.h"
#include "Player/SCharacter.h"
#include "AI/SZombieCharacter.h"

int32 Num = 0;
int32 NeedCreateZombieNum = 0;
ASurvivalGame_1GameModeBase::ASurvivalGame_1GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentTime = 0;
	MaxZombieNum = 1;
	CurrentZombieNum = 0;
	Wave = 1;
}
void ASurvivalGame_1GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentPlayerPawn = Cast<ASCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());	//获取当前PlayerPawn
	NeedCreateZombieNum = 0;
	if (CurrentPlayerPawn)
	{
		GetWorldTimerManager().SetTimer(mTimerHandle, this, &ASurvivalGame_1GameModeBase::Timeing, 1, true);	//每秒调用计时函数
		CurentZombie(MaxZombieNum);
	}
}

void ASurvivalGame_1GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASurvivalGame_1GameModeBase::Timeing()
{
	if (CurrentPlayerPawn->IsAlive())	//检查玩家是否存活
	{
		CurrentTime++;


	}
	if (NeedCreateZombieNum != MaxZombieNum)	//如果需要创建的僵尸数量不够最大值
	{
		CurentZombie(MaxZombieNum - NeedCreateZombieNum);	//将剩余需要创建的数量传入
	}

	if (CurrentZombieNum <= 0 && NeedCreateZombieNum == MaxZombieNum)	//如果需要创建的僵尸数量已经创建完毕并且场上已经没有僵尸就准备创建下一波
	{
		Wave++;
		MaxZombieNum += 1;
		NeedCreateZombieNum = 0;
	}
}

void ASurvivalGame_1GameModeBase::CurentZombie(int32 CurentZombieNum)
{
	for (size_t i = 0; i < CurentZombieNum; i++)
	{
		
		if (CurrentZombieLocation.Num() == Num)		//如果创建的位置已满就等待下次在创建
		{
			Num = 0;
			GetWorld()->SpawnActor<ASZombieCharacter>(CurentZombieClass_2, CurrentZombieLocation[Num]);
			CurrentZombieNum++;
			NeedCreateZombieNum++;
			break;
		}
		GetWorld()->SpawnActor<ASZombieCharacter>(CurentZombieClass, CurrentZombieLocation[Num]);
		CurrentZombieNum++;
		NeedCreateZombieNum++;
		Num++;
	}
}
