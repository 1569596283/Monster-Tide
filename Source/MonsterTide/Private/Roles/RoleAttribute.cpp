// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/RoleAttribute.h"
#include "Data/RolePropertyData.h"

void URoleAttribute::SetBaseProperty(FRoleProperty& RP)
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
		RoleProperty->RecoveryHP = BaseRoleProperty->RecoveryHP;
		RoleProperty->MaxMP = BaseRoleProperty->MaxMP;
		RoleProperty->MP = RoleProperty->MaxMP * MPPercent;
		RoleProperty->RecoveryMP = BaseRoleProperty->RecoveryMP;
		RoleProperty->Attack = BaseRoleProperty->Attack;
		RoleProperty->Defense = BaseRoleProperty->Defense;
	}
	OnRolePropertyChanged.ExecuteIfBound();
}

void URoleAttribute::AddLevel(int CurLevel, int TargetLevel)
{
	GetTargetLevelProperty(BaseRoleProperty, CurLevel, TargetLevel);
	RefreshRoleProperty();
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
	OnRoleHPChanged.ExecuteIfBound();
}

void URoleAttribute::ChangeMP(float Value)
{
	RoleProperty->MP = FMath::Clamp(RoleProperty->MP + Value, 0, RoleProperty->MaxMP);
	OnRoleMPChanged.ExecuteIfBound();
}

void URoleAttribute::RecoveryProperty(float Time)
{
	ChangeHP(Time * RoleProperty->RecoveryHP);
	ChangeMP(Time * RoleProperty->RecoveryMP);
}

void URoleAttribute::RecoveryAllStatuses()
{
	RoleProperty->HP = RoleProperty->MaxHP;
	RoleProperty->MP = RoleProperty->MaxMP;
}
