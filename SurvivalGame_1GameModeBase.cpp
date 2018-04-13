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

	CurrentPlayerPawn = Cast<ASCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());	//��ȡ��ǰPlayerPawn
	NeedCreateZombieNum = 0;
	if (CurrentPlayerPawn)
	{
		GetWorldTimerManager().SetTimer(mTimerHandle, this, &ASurvivalGame_1GameModeBase::Timeing, 1, true);	//ÿ����ü�ʱ����
		CurentZombie(MaxZombieNum);
	}
}

void ASurvivalGame_1GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASurvivalGame_1GameModeBase::Timeing()
{
	if (CurrentPlayerPawn->IsAlive())	//�������Ƿ���
	{
		CurrentTime++;


	}
	if (NeedCreateZombieNum != MaxZombieNum)	//�����Ҫ�����Ľ�ʬ�����������ֵ
	{
		CurentZombie(MaxZombieNum - NeedCreateZombieNum);	//��ʣ����Ҫ��������������
	}

	if (CurrentZombieNum <= 0 && NeedCreateZombieNum == MaxZombieNum)	//�����Ҫ�����Ľ�ʬ�����Ѿ�������ϲ��ҳ����Ѿ�û�н�ʬ��׼��������һ��
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
		
		if (CurrentZombieLocation.Num() == Num)		//���������λ�������͵ȴ��´��ڴ���
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
