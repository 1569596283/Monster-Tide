// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/RolePropertyData.h"

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

FRoleProperty* getRandomRoleProperty(ERoleType type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_RoleProperty.DT_RoleProperty'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(type).ToString());
		FRolePropertyConfig* RolePropertyConfig = DataTable->FindRow<FRolePropertyConfig>(RowName, ContextString);
		if (RolePropertyConfig) {
			FRoleProperty* rp = new FRoleProperty(*RolePropertyConfig);
			return rp;
		}
	}
	return nullptr;
}

TSubclassOf<class ARoleBase> GetRoleSubclass(ERoleType type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_RoleProperty.DT_RoleProperty'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(type).ToString());
		FRolePropertyConfig* RolePropertyConfig = DataTable->FindRow<FRolePropertyConfig>(RowName, ContextString);
		if (RolePropertyConfig) {
			return RolePropertyConfig->RoleClass;
		}
	}
	return NULL;
}
