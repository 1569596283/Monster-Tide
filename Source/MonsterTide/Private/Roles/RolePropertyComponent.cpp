// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/RolePropertyComponent.h"
#include "UI/Game/UI_RoleProperty.h"
#include "Data/RolePropertyData.h"

bool URolePropertyComponent::InitProperty(FRoleProperty* rp)
{
	RoleProperty = rp;
	UMG_RoleProperty = Cast<UUI_RoleProperty>(GetWidget());
	RefreshProperty();
	return true;
}

void URolePropertyComponent::RefreshProperty()
{
	UMG_RoleProperty->SetLevel(RoleProperty->Level);
	UMG_RoleProperty->SetHP(RoleProperty->HP / RoleProperty->MaxHP);
	UMG_RoleProperty->SetMP(RoleProperty->MP / RoleProperty->MaxMP);
}
