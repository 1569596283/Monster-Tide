// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/RolePropertyComponent.h"
#include "Roles/RoleAttribute.h"
#include "UI/Game/UI_RoleProperty.h"
#include "Data/RolePropertyData.h"

bool URolePropertyComponent::InitProperty(int Level, const TObjectPtr<URoleAttribute> RA)
{
	UMG_RoleProperty = Cast<UUI_RoleProperty>(GetWidget());
	UMG_RoleProperty->SetLevel(Level);
	RoleProperty = RA->GetRoleProperty();
	RefreshProperty();
	RA->OnRolePropertyChanged.BindDynamic(this, &URolePropertyComponent::RefreshProperty);
	RA->OnRoleHPChanged.BindDynamic(this, &URolePropertyComponent::RefreshHP);
	RA->OnRoleMPChanged.BindDynamic(this, &URolePropertyComponent::RefreshMP);
	return true;
}

void URolePropertyComponent::RefreshProperty()
{
	RefreshHP();
	RefreshMP();
}

void URolePropertyComponent::RefreshLevel(int Level)
{
	UMG_RoleProperty->SetLevel(Level);
}

void URolePropertyComponent::RefreshHP()
{
	UMG_RoleProperty->SetHP(RoleProperty->HP / RoleProperty->MaxHP);
}

void URolePropertyComponent::RefreshMP()
{
	UMG_RoleProperty->SetMP(RoleProperty->MP / RoleProperty->MaxMP);
}
