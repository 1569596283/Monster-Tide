// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/RolePropertyData.h"
#include "Roles/Heros/HeroBase.h"
#include "Roles/Enemys/EnemyBase.h"

FRoleProperty::FRoleProperty()
{
}

FRoleProperty::FRoleProperty(const FRoleProperty& Other)
{
	Type = Other.Type;
	Level = Other.Level;
	Exp = Other.Exp;
	MaxHP = Other.MaxHP;
	HP = Other.HP;
	RecoveryHP = Other.RecoveryHP;
	MaxMP = Other.MaxMP;
	MP = Other.MP;
	RecoveryMP = Other.RecoveryMP;
	Attack = Other.Attack;
	Defense = Other.Defense;
	Speed = Other.Speed;
	Range = Other.Range;
	SkillInterval = Other.SkillInterval;
	Skill = Other.Skill;
}

FRoleProperty::FRoleProperty(const FRolePropertyConfig& Config)
{
	Type = Config.Type;
	Level = 1;
	Exp = 0;
	MaxHP = FMath::RandRange(Config.MinHP, Config.MaxHP);
	HP = MaxHP;
	RecoveryHP = Config.RecoveryHP;
	MaxMP = FMath::RandRange(Config.MinMP, Config.MaxMP);
	MP = MaxMP;
	RecoveryMP = Config.RecoveryMP;
	Attack = FMath::RandRange(Config.MinAttack, Config.MaxAttack);
	Defense = FMath::RandRange(Config.MinDefense, Config.MaxDefense);
	Speed = Config.Speed;
	Range = Config.Range;
	SkillInterval = Config.SkillInterval;
	Skill = Config.Skill;
}

FRoleProperty* GetTargetLevelProperty(FRoleProperty* Property, int TargetLevel)
{
	if (Property->Level == TargetLevel) {
		return Property;
	}

	for (int level = Property->Level; level <= TargetLevel; level += 1) {
		float multiplier = level % 9 == 0 ? 2.f : 1.1f;
		Property->MaxHP *= multiplier;
		Property->HP *= multiplier;
		Property->MaxMP *= multiplier;
		Property->MP *= multiplier;
		Property->Attack *= multiplier;
		Property->Defense *= multiplier;
	}
	Property->Level = TargetLevel;

	return Property;
}

TObjectPtr<USkeletalMesh> GetHeroSkeletalMesh(ERoleType Type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_HeroProperty.DT_HeroProperty'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(Type).ToString());
		FHeroPropertyConfig* HeroPropertyConfig = DataTable->FindRow<FHeroPropertyConfig>(RowName, ContextString);
		if (HeroPropertyConfig) {
			return HeroPropertyConfig->SkeletalMesh;
		}
	}
	return nullptr;
}

FRoleProperty* GetRandomHeroProperty(ERoleType Type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_HeroProperty.DT_HeroProperty'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(Type).ToString());
		FHeroPropertyConfig* HeroPropertyConfig = DataTable->FindRow<FHeroPropertyConfig>(RowName, ContextString);
		if (HeroPropertyConfig) {
			FRoleProperty* rp = new FRoleProperty(*HeroPropertyConfig);
			return rp;
		}
	}
	return nullptr;
}

FHeroPropertyConfig* GetHeroPropertyConfig(ERoleType Type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_HeroProperty.DT_HeroProperty'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(Type).ToString());
		FHeroPropertyConfig* HeroPropertyConfig = DataTable->FindRow<FHeroPropertyConfig>(RowName, ContextString);
		if (HeroPropertyConfig) {
			return HeroPropertyConfig;
		}
	}
	return nullptr;
}

FRoleProperty* GetRandomEnemyProperty(ERoleType Type, int Level)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_EnemyProperty.DT_EnemyProperty'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(Type).ToString());
		FEnemyPropertyConfig* EnemyPropertyConfig = DataTable->FindRow<FEnemyPropertyConfig>(RowName, ContextString);
		if (EnemyPropertyConfig) {
			FRoleProperty* rp = new FRoleProperty(*EnemyPropertyConfig);
			rp->Exp = EnemyPropertyConfig->BaseExp * (1 + Level / 10);
			GetTargetLevelProperty(rp, Level);
			return rp;
		}
	}
	return nullptr;
}

FEnemyPropertyConfig* GetEnemyPropertyConfig(ERoleType Type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_EnemyProperty.DT_EnemyProperty'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(Type).ToString());
		FEnemyPropertyConfig* EnemyPropertyConfig = DataTable->FindRow<FEnemyPropertyConfig>(RowName, ContextString);
		if (EnemyPropertyConfig) {
			return EnemyPropertyConfig;
		}
	}
	return nullptr;
}
