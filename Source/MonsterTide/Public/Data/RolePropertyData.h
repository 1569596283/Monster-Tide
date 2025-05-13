// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RolePropertyData.generated.h"

/* ��ɫ���ͣ�����Ӣ�ۺ͵��� */
UENUM(BlueprintType)
enum class ERoleType :uint8 {
	Role	UMETA(DisplayName = "Role"),
	Hero	UMETA(DisplayName = "Hero"),
	Enemy	UMETA(DisplayName = "Enemy")
};

/* ��ɫ���� */
USTRUCT(BlueprintType)
struct FRoleProperty
{
	GENERATED_BODY()

	FRoleProperty();

	FRoleProperty(const FRoleProperty& Other);

	FRoleProperty(const FRolePropertyConfig& Config);

	UPROPERTY(EditDefaultsOnly)
	ERoleType Type = ERoleType::Role;

	UPROPERTY(EditDefaultsOnly)
	int Level = 1;

	UPROPERTY(EditDefaultsOnly)
	float Exp = 0;

	UPROPERTY(EditDefaultsOnly)
	float MaxHP = 100;

	UPROPERTY(EditDefaultsOnly)
	float HP = 100;

	UPROPERTY(EditDefaultsOnly)
	float MaxMP = 100;

	UPROPERTY(EditDefaultsOnly)
	float MP = 100;

	UPROPERTY(EditDefaultsOnly)
	float Attack = 100;

	UPROPERTY(EditDefaultsOnly)
	float Defense = 0;
};

/* ��ɫ�������� */
USTRUCT(BlueprintType)
struct FRolePropertyConfig :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	ERoleType Type = ERoleType::Role;

	UPROPERTY(EditDefaultsOnly)
	float MinHP = 100;
	UPROPERTY(EditDefaultsOnly)
	float MaxHP = 100;
	UPROPERTY(EditDefaultsOnly)
	float MinMP = 100;
	UPROPERTY(EditDefaultsOnly)
	float MaxMP = 100;
	UPROPERTY(EditDefaultsOnly)
	float MinAttack = 10;
	UPROPERTY(EditDefaultsOnly)
	float MaxAttack = 10;
	UPROPERTY(EditDefaultsOnly)
	float MinDefense = 0;
	UPROPERTY(EditDefaultsOnly)
	float MaxDefense = 0;
};

class AEnemyBase;
class AHeroBase;


/* ������������ */
USTRUCT(BlueprintType)
struct FEnemyPropertyConfig :public FRolePropertyConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyBase> EnemyClass;

	UPROPERTY(EditDefaultsOnly)
	int Damage = 1;
};

/* Ӣ���������� */
USTRUCT(BlueprintType)
struct FHeroPropertyConfig :public FRolePropertyConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHeroBase> HeroClass;
};

FRoleProperty* getRandomHeroProperty(ERoleType type);
FHeroPropertyConfig* GetHeroPropertyConfig(ERoleType type);
FRoleProperty* getRandomEnemyProperty(ERoleType type);
FEnemyPropertyConfig* GetEnemyPropertyConfig(ERoleType type);