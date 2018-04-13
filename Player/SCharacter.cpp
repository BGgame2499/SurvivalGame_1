// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine.h"
#include "Weapon/SWeapon.h"

ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	isFire = false;

	UCharacterMovementComponent * MoveComp = GetCharacterMovement();	//��ʼ������Movement���
	MoveComp->GravityScale = 1.5f;
	MoveComp->JumpZVelocity = 650.0f;
	MoveComp->bCanWalkOffLedgesWhenCrouching = true;
	MoveComp->MaxWalkSpeedCrouched = 150.0f;	//����ܲ��ٶ�

	CameraBoomComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));	//��ʼ��������ֱ�
	CameraBoomComp->SocketOffset = FVector(0, 35, 0);
	CameraBoomComp->TargetOffset = FVector(0, 0, 55);
	CameraBoomComp->bUsePawnControlRotation = true;	//��������ɫ��ת
	CameraBoomComp->SetupAttachment(GetRootComponent());

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));	//��ʼ�����
	CameraComp->SetupAttachment(CameraBoomComp);	//�������������Ϊ������ֱ�

	WeaponScene_1 = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponScene"));	//��ʼ��������λ
	WeaponScene_1->SetupAttachment(GetMesh(),TEXT("WeaponSocket"));

}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeapon = GetWorld()->SpawnActor<ASWeapon>(WeaponClass, FVector(0, 0, 0), FRotator(0, 0, 0));	//����ָ����������
	CurrentWeapon->AttachToComponent(WeaponScene_1, FAttachmentTransformRules::KeepRelativeTransform);	//�󶨵�������λ
}

void ASCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)	//������
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);	//ǰ���ƶ�
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);	//�����ƶ�
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);	//�ӽ������ƶ�
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);//�ӽ������ƶ�

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASCharacter::OnStartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASCharacter::OnStopFire);
}


bool ASCharacter::GetIsFire()	//�����Ƿ񿪻�
{
	return isFire;
}

void ASCharacter::MoveForward(float Val)
{
	if (Val != 0)	//����ٶ��Ƿ�Ϊ0
	{
		const FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::X);	//��ȡ��ǰ��ҷ����Xֵ	
		AddMovementInput(Direction, Val);
	}
}

void ASCharacter::MoveRight(float Val)
{
	if (Val != 0)
	{
		const FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y);	//��ȡ��ǰ��ҷ����Xֵ	
		AddMovementInput(Direction, Val);
	}
}

void ASCharacter::OnStartFire()	//����
{
	if (GetCharacterMovement()->MovementMode != EMovementMode::MOVE_Falling)	//����ɫ�Ƿ��ڿ���
	{
		isFire = true;
		CurrentWeapon->OnFire();	//������������
	}
}

void ASCharacter::OnStopFire()	//ͣ��
{
	isFire = false;
	CurrentWeapon->EndFire();	//��������ͣ��
}
