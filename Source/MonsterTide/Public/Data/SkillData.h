// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillData.generated.h"


/* 技能类型 */
UENUM(BlueprintType)
enum class ESkillType :uint8 {
	SkillBase	UMETA(DisplayName = "SkillBase"),
	Skill_1	UMETA(DisplayName = "Skill_1"),
	Skill_2	UMETA(DisplayName = "Skill_2"),
	Skill_3	UMETA(DisplayName = "Skill_3"),
	Skill_4	UMETA(DisplayName = "Skill_4"),
};


/* 角色属性配置 */
USTRUCT(BlueprintType)
struct FSkillConfig :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	ESkillType Type = ESkillType::SkillBase;

	UPROPERTY(EditDefaultsOnly)
	float Multiple = 1.f;

	UPROPERTY(EditDefaultsOnly)
	float Range = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float Consume = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float CD = 1.f;

	UPROPERTY(EditDefaultsOnly)
	int Speed = 500;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASkillBase> SkillClass;
};

FSkillConfig* GetSkillConfig(ESkillType Type);