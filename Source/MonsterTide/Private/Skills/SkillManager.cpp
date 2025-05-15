// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/SkillManager.h"
#include "Roles/HeroManager.h"

void USkillManager::InitSkill()
{
	// 这个委托没有清理，会一直累加
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->OnRoleUseSkill.AddUObject(this, &USkillManager::RoleUseSkill);
}

void USkillManager::RoleUseSkill(ESkillType Type, TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target)
{
	UE_LOG(LogTemp, Warning, TEXT("USkillManager::RoleUseSkill "));
}
