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
	MaxMP = Other.MaxMP;
	MP = Other.MP;
	Attack = Other.Attack;
	Defense = Other.Defense;
}

FRoleProperty::FRoleProperty(const FRolePropertyConfig& Config)
{
	Type = Config.Type;
	Level = 1;
	Exp = 0;
	MaxHP = FMath::RandRange(Config.MinHP, Config.MaxHP);
	HP = MaxHP;
	MaxMP = FMath::RandRange(Config.MinMP, Config.MaxMP);
	MP = MaxMP;
	Attack = FMath::RandRange(Config.MinAttack, Config.MaxAttack);
	Defense = FMath::RandRange(Config.MinDefense,Config.MaxDefense);
}

FRoleProperty* getRandomHeroProperty(ERoleType type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_HeroProperty.DT_HeroProperty'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(type).ToString());
		FHeroPropertyConfig* HeroPropertyConfig = DataTable->FindRow<FHeroPropertyConfig>(RowName, ContextString);
		if (HeroPropertyConfig) {
			FRoleProperty* rp = new FRoleProperty(*HeroPropertyConfig);
			return rp;
		}
	}
	return nullptr;
}

TSubclassOf<AHeroBase> GetHeroSubclass(ERoleType type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_HeroProperty.DT_HeroProperty'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(type).ToString());
		FHeroPropertyConfig* HeroPropertyConfig = DataTable->FindRow<FHeroPropertyConfig>(RowName, ContextString);
		if (HeroPropertyConfig) {
			return HeroPropertyConfig->RoleClass;
		}
	}
	return NULL;
}

FRoleProperty* getRandomEnemyProperty(ERoleType type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_EnemyProperty.DT_EnemyProperty'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(type).ToString());
		FEnemyPropertyConfig* EnemyPropertyConfig = DataTable->FindRow<FEnemyPropertyConfig>(RowName, ContextString);
		if (EnemyPropertyConfig) {
			FRoleProperty* rp = new FRoleProperty(*EnemyPropertyConfig);
			return rp;
		}
	}
	return nullptr;
}

TSubclassOf<AEnemyBase> GetEnemySubclass(ERoleType type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_EnemyProperty.DT_EnemyProperty'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(type).ToString());
		FEnemyPropertyConfig* EnemyPropertyConfig = DataTable->FindRow<FEnemyPropertyConfig>(RowName, ContextString);
		if (EnemyPropertyConfig) {
			return EnemyPropertyConfig->RoleClass;
		}
	}
	return NULL;
}
