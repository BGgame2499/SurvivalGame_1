// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine.h"
#include "Weapon/SWeapon.h"

ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	isFire = false;

	UCharacterMovementComponent * MoveComp = GetCharacterMovement();	//初始化设置Movement组件
	MoveComp->GravityScale = 1.5f;
	MoveComp->JumpZVelocity = 650.0f;
	MoveComp->bCanWalkOffLedgesWhenCrouching = true;
	MoveComp->MaxWalkSpeedCrouched = 150.0f;	//最大跑步速度

	CameraBoomComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));	//初始化摄像机手臂
	CameraBoomComp->SocketOffset = FVector(0, 35, 0);
	CameraBoomComp->TargetOffset = FVector(0, 0, 55);
	CameraBoomComp->bUsePawnControlRotation = true;	//允许跟随角色旋转
	CameraBoomComp->SetupAttachment(GetRootComponent());

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));	//初始化相机
	CameraComp->SetupAttachment(CameraBoomComp);	//将相机父类设置为摄像机手臂

	WeaponScene_1 = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponScene"));	//初始化武器槽位
	WeaponScene_1->SetupAttachment(GetMesh(),TEXT("WeaponSocket"));

}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeapon = GetWorld()->SpawnActor<ASWeapon>(WeaponClass, FVector(0, 0, 0), FRotator(0, 0, 0));	//生成指定类型武器
	CurrentWeapon->AttachToComponent(WeaponScene_1, FAttachmentTransformRules::KeepRelativeTransform);	//绑定到武器槽位
}

void ASCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)	//按键绑定
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);	//前后移动
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);	//左右移动
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);	//视角左右移动
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);//视角上下移动

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASCharacter::OnStartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASCharacter::OnStopFire);
}


bool ASCharacter::GetIsFire()	//返回是否开火
{
	return isFire;
}

void ASCharacter::MoveForward(float Val)
{
	if (Val != 0)	//检查速度是否为0
	{
		const FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::X);	//获取当前玩家方向的X值	
		AddMovementInput(Direction, Val);
	}
}

void ASCharacter::MoveRight(float Val)
{
	if (Val != 0)
	{
		const FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y);	//获取当前玩家方向的X值	
		AddMovementInput(Direction, Val);
	}
}

void ASCharacter::OnStartFire()	//开火
{
	if (GetCharacterMovement()->MovementMode != EMovementMode::MOVE_Falling)	//检查角色是否在空中
	{
		isFire = true;
		CurrentWeapon->OnFire();	//调用武器开火
	}
}

void ASCharacter::OnStopFire()	//停火
{
	isFire = false;
	CurrentWeapon->EndFire();	//调用武器停火
}
