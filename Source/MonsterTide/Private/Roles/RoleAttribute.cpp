// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/RoleAttribute.h"
#include "Data/RolePropertyData.h"

void URoleAttribute::SetBaseProperty(const FRoleProperty& RP)
{
	BaseRoleProperty = new FRoleProperty(RP);
	RefreshRoleProperty();
}

void URoleAttribute::RefreshRoleProperty()
{
	if (RoleProperty == nullptr) {
		RoleProperty = new FRoleProperty(*BaseRoleProperty);
	}
	else {
		float HPPercent = RoleProperty->HP / RoleProperty->MaxHP;
		float MPPercent = RoleProperty->MP / RoleProperty->MaxMP;
		RoleProperty->MaxHP = BaseRoleProperty->MaxHP;
		RoleProperty->HP = RoleProperty->MaxHP * HPPercent;
		RoleProperty->MaxMP = BaseRoleProperty->MaxMP;
		RoleProperty->MP = RoleProperty->MaxMP * MPPercent;
		RoleProperty->Attack = BaseRoleProperty->Attack;
		RoleProperty->Defense = BaseRoleProperty->Defense;
	}
}

const FRoleProperty* URoleAttribute::GetRoleProperty() const
{
	return RoleProperty;
}

const FRoleProperty* URoleAttribute::GetBaseProperty() const
{
	return BaseRoleProperty;
}

bool URoleAttribute::IsDead()
{
	return RoleProperty->HP <= 0;
}

void URoleAttribute::ChangeHP(float Value)
{
	RoleProperty->HP = FMath::Clamp(RoleProperty->HP + Value, 0, RoleProperty->MaxHP);
}

void URoleAttribute::ChangeMP(float Value)
{
	RoleProperty->MP = FMath::Clamp(RoleProperty->MP + Value, 0, RoleProperty->MaxMP);
}

void URoleAttribute::AddExp(float Exp)
{
	float TargetExp = 100.f * BaseRoleProperty->Level;
	BaseRoleProperty->Exp += Exp;
	bool Up = BaseRoleProperty->Exp >= TargetExp;
	while (BaseRoleProperty->Exp >= TargetExp) {
		BaseRoleProperty->Exp -= TargetExp;
		LevelUp(BaseRoleProperty->Level + 1);
		TargetExp = 100.f * BaseRoleProperty->Level;
	}
	if (Up) {
		RefreshRoleProperty();
	}
}

void URoleAttribute::LevelUp(int TargetLevel)
{
	GetTargetLevelProperty(BaseRoleProperty, TargetLevel);
}
