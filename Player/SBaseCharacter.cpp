
#include "SBaseCharacter.h"


ASBaseCharacter::ASBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Health = 100.0f;
}

void ASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsAlive())		//检查是否存活
	{
		ToDeath();
	}
}


float ASBaseCharacter::GetHealth() const	//获取当前血量
{
	return Health / 100;
}

float ASBaseCharacter::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<ASBaseCharacter>()->Health;	//返回初始化时的血量
}

bool ASBaseCharacter::IsAlive() const
{
	return Health > 0;
}

void ASBaseCharacter::ToDeath()	//死亡执行函数
{
	Destroy();
}

FRotator ASBaseCharacter::GetAimOffsets() const	//获取当前瞄准位置
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
}

//接受伤害
float ASBaseCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (Health <= 0.f)	//如果玩家已死返回0
	{
		return 0.0f;
	}
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);	//计算实际伤害
	if (ActualDamage >= 0.f)
	{
		Health -= ActualDamage;	//伤害不等于0就减血
	}
	return ActualDamage;
}

