
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

	if (!IsAlive())		//����Ƿ���
	{
		ToDeath();
	}
}


float ASBaseCharacter::GetHealth() const	//��ȡ��ǰѪ��
{
	return Health / 100;
}

float ASBaseCharacter::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<ASBaseCharacter>()->Health;	//���س�ʼ��ʱ��Ѫ��
}

bool ASBaseCharacter::IsAlive() const
{
	return Health > 0;
}

void ASBaseCharacter::ToDeath()	//����ִ�к���
{
	Destroy();
}

FRotator ASBaseCharacter::GetAimOffsets() const	//��ȡ��ǰ��׼λ��
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
}

//�����˺�
float ASBaseCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (Health <= 0.f)	//��������������0
	{
		return 0.0f;
	}
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);	//����ʵ���˺�
	if (ActualDamage >= 0.f)
	{
		Health -= ActualDamage;	//�˺�������0�ͼ�Ѫ
	}
	return ActualDamage;
}

