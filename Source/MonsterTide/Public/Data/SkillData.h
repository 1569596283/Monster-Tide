// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillData.generated.h"


/* 技能类型 */
UENUM(BlueprintType)
enum class ESkillType :uint8 {
	Skill	UMETA(DisplayName = "Skill"),
};


/* 角色属性配置 */
USTRUCT(BlueprintType)
struct FSkillConfig :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	ESkillType Type = ESkillType::Skill;

	UPROPERTY(EditDefaultsOnly)
	float Multiple = 1.f;

	UPROPERTY(EditDefaultsOnly)
	float Range = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float Consume = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float CD = 1.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASkillBase> SkillClass;
};

FSkillConfig* GetSkillConfig(ESkillType Type);