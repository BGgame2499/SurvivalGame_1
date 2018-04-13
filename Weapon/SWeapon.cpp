
#include "SWeapon.h"
#include "Engine.h"
#include "Bullet/SBaseBullet.h"

ASWeapon::ASWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	RootComponent = WeaponMesh;

	BulletScene = CreateDefaultSubobject<USceneComponent>(TEXT("BulletScene"));
	BulletScene->SetupAttachment(WeaponMesh, TEXT("MuzzleFlashSocket"));

	WeaponDamage = 20.0f;	//��ʼ�������˺�ֵ
	BulletBoxMaxNum = 30;	//��ʼ��Ĭ����󵯼��ӵ�����
	BulletCurrentNum = BulletBoxMaxNum;	//��ʼ����ǰ�ӵ�����
	FiringSpeed = 0.15f;		//��ʼ�����������ٶ�

	CurrentWeaponState = EWeaponState::Idle;	//��ʼ������״̬
}

void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(mTimerHandle, this, &ASWeapon::CreateBullet, FiringSpeed, true);
}

void ASWeapon::OnFire()
{
	if (CurrentWeaponState == EWeaponState::Idle)
	{
		CurrentWeaponState = EWeaponState::Firing;
		//CreateBullet();
	}
}

void ASWeapon::EndFire()
{
	if (CurrentWeaponState == EWeaponState::Firing)
	{
		CurrentWeaponState = EWeaponState::Idle;

	}
}

int32 ASWeapon::GetBulletCurrentNum() const
{
	return BulletCurrentNum;
}

void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASWeapon::CreateBullet()
{
	if (CurrentWeaponState == EWeaponState::Firing)
	{
		FVector Vect = BulletScene->GetComponentLocation();
		FRotator Rot = BulletScene->GetComponentRotation();
		if (FireParticle && FireSound)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, FireParticle, Vect, Rot);
			UGameplayStatics::SpawnSoundAttached(FireSound, this->GetRootComponent());
		}
		ASBaseBullet * thisBullet = GetWorld()->SpawnActor<ASBaseBullet>(BulletClass, Vect, Rot);
		thisBullet->BulletDamage = WeaponDamage;

	}
}

