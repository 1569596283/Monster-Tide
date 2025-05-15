// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/SkillManager.h"
#include "Roles/HeroManager.h"
#include "Roles/RoleBase.h"
#include "Data/SkillData.h"
#include "Skills/SkillBase.h"

void USkillManager::InitSkill()
{
	// 这个委托没有清理，会一直累加
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->OnRoleUseSkill.AddUObject(this, &USkillManager::RoleUseSkill);
}

void USkillManager::RoleUseSkill(ESkillType Type, TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target)
{
	FVector SpawnLocation = User->GetActorLocation(); // 生成位置
	FRotator SpawnRotation(0, 0, 0);	// 生成旋转
	FVector Direction = Target->GetActorLocation() - User->GetActorLocation();
	Direction.Z = 0; // 如果不需要垂直方向旋转，可以忽略Z轴
	// 只有当方向有效时才旋转
	if (!Direction.IsNearlyZero())
	{
		SpawnRotation = Direction.Rotation();
	}
	FSkillConfig* SkillConfig = GetSkillConfig(Type);
	TSubclassOf<ASkillBase> SkillClass = SkillConfig->SkillClass;
	if (SkillClass) {
		ASkillBase* Skill = GetWorld()->SpawnActor<ASkillBase>(SkillClass, SpawnLocation, SpawnRotation);
		Skill->InitSkill(Type, User, Target);
	}
}
