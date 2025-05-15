// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/SkillManager.h"
#include "Roles/HeroManager.h"
#include "Roles/RoleBase.h"
#include "Data/SkillData.h"
#include "Skills/SkillBase.h"

void USkillManager::InitSkill()
{
	// ���ί��û��������һֱ�ۼ�
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->OnRoleUseSkill.AddUObject(this, &USkillManager::RoleUseSkill);
}

void USkillManager::RoleUseSkill(ESkillType Type, TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target)
{
	FVector SpawnLocation = User->GetActorLocation(); // ����λ��
	FRotator SpawnRotation(0, 0, 0);	// ������ת
	FVector Direction = Target->GetActorLocation() - User->GetActorLocation();
	Direction.Z = 0; // �������Ҫ��ֱ������ת�����Ժ���Z��
	// ֻ�е�������Чʱ����ת
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
