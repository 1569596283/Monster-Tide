// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/RoleAnimInstance.h"

float URoleAnimInstance::PlayAttackAnimation()
{
	if (AttackMontage)
	{
		return Montage_Play(AttackMontage);
	}
	return 0.f;
}

void URoleAnimInstance::SetState(ERoleAnimState State)
{
	RoleAnimState = State;
}

void URoleAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void URoleAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
}
