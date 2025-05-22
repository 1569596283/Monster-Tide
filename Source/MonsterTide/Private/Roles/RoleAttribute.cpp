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

}

const FRoleProperty* URoleAttribute::GetRoleProperty() const
{
	return RoleProperty;
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
