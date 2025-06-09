// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/Heros/HeroBase.h"
#include "Roles/Enemys/EnemyBase.h"
#include "Roles/RoleAttribute.h"
#include "Roles/RoleAnimInstance.h"
#include "Data/RolePropertyData.h"
#include "Components/CapsuleComponent.h"
#include "Data/SkillData.h"
#include "Roles/RolePropertyComponent.h"

AHeroBase::AHeroBase()
{
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	if (Capsule)
	{
		Capsule->SetCollisionProfileName(TEXT("Hero"));
	}
}

TObjectPtr<AEnemyBase> AHeroBase::GetTargetEnemy()
{
	TArray<TObjectPtr<AActor>> ActorArr = GetTargetWithinRange(ECC_GameTraceChannel2);
	TObjectPtr<AEnemyBase> TargetEnemy = nullptr;
	for (int i = 0; i < ActorArr.Num(); i++) {
		if (TObjectPtr<AEnemyBase> Enemy = Cast<AEnemyBase>(ActorArr[i])) {
			if (!Enemy->IsDead() && (TargetEnemy == nullptr || Enemy->GetRemainDistance() < TargetEnemy->GetRemainDistance())) {
				TargetEnemy = Enemy;
			}
		}
	}
	return TargetEnemy;
}

void AHeroBase::LookAtEnemy()
{
	TObjectPtr<AEnemyBase> TargetEnemy = GetTargetEnemy();
	if (TargetEnemy != nullptr) {
		// 计算方向向量
		FVector Direction = TargetEnemy->GetActorLocation() - this->GetActorLocation();
		Direction.Z = 0; // 如果不需要垂直方向旋转，可以忽略Z轴

		// 只有当方向有效时才旋转
		if (!Direction.IsNearlyZero())
		{
			FRotator NewRotation = Direction.Rotation();
			SetActorRotation(NewRotation);
		}
	}
}

void AHeroBase::Tick(float DeltaTime)
{
	LookAtEnemy();
	Super::Tick(DeltaTime);
}

void AHeroBase::RefreshProperty(TObjectPtr<URoleAttribute> Attribute, int Level, float Exp)
{
	if (Attribute == RoleAttribute) {
		RolePropertyComponent->RefreshLevel(Level);
	}
}

float AHeroBase::UseSkill()
{
	TObjectPtr<AEnemyBase> TargetEnemy = GetTargetEnemy();
	if (TargetEnemy != nullptr) {
		int index = GetNextSkill();
		if (index < 0) {
			return RoleAttribute->GetRoleProperty()->SkillInterval;
		}
		FSkillConfig* SkillConfig = &RoleSkill.SkillConfigArray[index];
		RoleSkill.SkillCD[index] = SkillConfig->CD;
		float Consume = SkillConfig->Consume;
		RoleAttribute->ChangeMP(-Consume);
		float Damage = Consume * GetRoleProperty()->Attack * SkillConfig->Multiple;
		float Time = RoleAnimInstance->PlayAttackAnimation();
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			[this, SkillConfig, Damage, TargetEnemy]()
			{
				OnRoleUseSkill.Broadcast(SkillConfig->Type, Damage, this, TargetEnemy);
			},
			Time / 2,
			false
		);
		// 后面改成这个技能的释放时间和角色技能间隔的较大值
	}
	return GetRoleProperty()->SkillInterval;
}
