// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RolePropertyData.generated.h"

enum class ESkillType :uint8;

/* 角色类型，包括英雄和敌人 */
UENUM(BlueprintType)
enum class ERoleType :uint8 {
	Role	UMETA(DisplayName = "Role"),
	Hero_1	UMETA(DisplayName = "Hero_1"),
	Hero_2	UMETA(DisplayName = "Hero_2"),
	Hero_3	UMETA(DisplayName = "Hero_3"),
	Hero_4	UMETA(DisplayName = "Hero_4"),
	Enemy_1	UMETA(DisplayName = "Enemy_1"),
	Enemy_2	UMETA(DisplayName = "Enemy_2"),
	Enemy_3	UMETA(DisplayName = "Enemy_3"),
	Enemy_4	UMETA(DisplayName = "Enemy_4"),
	Enemy_5	UMETA(DisplayName = "Enemy_5")
};

/* 角色属性 */
USTRUCT(BlueprintType)
struct FRoleProperty
{
	GENERATED_BODY()

	FRoleProperty();

	FRoleProperty(const FRoleProperty& Other);

	FRoleProperty(const FRolePropertyConfig& Config);

	UPROPERTY(EditDefaultsOnly)
	float MaxHP = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float HP = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float RecoveryHP = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxMP = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float MP = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float RecoveryMP = 1.f;

	UPROPERTY(EditDefaultsOnly)
	float Attack = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float Defense = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float Speed = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float Range = 500.f;

	UPROPERTY(EditDefaultsOnly)
	float SkillInterval = 1.f;

	UPROPERTY(EditDefaultsOnly)
	TArray<ESkillType> Skill = {};
};

/* 角色属性配置 */
USTRUCT(BlueprintType)
struct FRolePropertyConfig :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	ERoleType Type = ERoleType::Role;

	UPROPERTY(EditDefaultsOnly)
	float MinHP = 100.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxHP = 100.f;
	UPROPERTY(EditDefaultsOnly)
	float RecoveryHP = 0.f;
	UPROPERTY(EditDefaultsOnly)
	float MinMP = 100.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxMP = 100.f;
	UPROPERTY(EditDefaultsOnly)
	float RecoveryMP = 1.f;
	UPROPERTY(EditDefaultsOnly)
	float MinAttack = 10.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxAttack = 10.f;
	UPROPERTY(EditDefaultsOnly)
	float MinDefense = 0.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxDefense = 0.f;
	UPROPERTY(EditDefaultsOnly)
	float Speed = 100.f;
	UPROPERTY(EditDefaultsOnly)
	float Range = 500.f;
	UPROPERTY(EditDefaultsOnly)
	float SkillInterval = 1.f;
	UPROPERTY(EditDefaultsOnly)
	TArray<ESkillType> Skill = {};
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr< USkeletalMesh >SkeletalMesh;
};

class AEnemyBase;
class AHeroBase;


/* 敌人属性配置 */
USTRUCT(BlueprintType)
struct FEnemyPropertyConfig :public FRolePropertyConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyBase> EnemyClass;

	UPROPERTY(EditDefaultsOnly)
	int Damage = 1;

	UPROPERTY(EditDefaultsOnly)
	float BaseExp = 5;
};

/* 英雄属性配置 */
USTRUCT(BlueprintType)
struct FHeroPropertyConfig :public FRolePropertyConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHeroBase> HeroClass;
};

FRoleProperty* GetTargetLevelProperty( FRoleProperty* Property, int CurLevel, int TargetLevel);
TObjectPtr< USkeletalMesh >GetHeroSkeletalMesh(ERoleType Type);

FRoleProperty* GetRandomHeroProperty(ERoleType Type);
FHeroPropertyConfig* GetHeroPropertyConfig(ERoleType Type);
FRoleProperty* GetRandomEnemyProperty(ERoleType Type, int Level = 0);
FEnemyPropertyConfig* GetEnemyPropertyConfig(ERoleType Type);