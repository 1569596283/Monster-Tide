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

const FRoleProperty* URolePropertyComponent::GetRoleProperty()
{
	return RoleProperty;
}

bool URolePropertyComponent::IsDead()
{
	return RoleProperty->HP <= 0;
}

float URolePropertyComponent::ChangeHP(float Value)
{
	RoleProperty->HP = FMath::Clamp(RoleProperty->HP + Value, 0.f, RoleProperty->MaxHP);
	UMG_RoleProperty->SetHP(RoleProperty->HP / RoleProperty->MaxHP);
	return RoleProperty->HP;
}

float URolePropertyComponent::ChangeMP(float Value)
{
	RoleProperty->MP = FMath::Clamp(RoleProperty->MP + Value, 0.f, RoleProperty->MaxMP);
	UMG_RoleProperty->SetMP(RoleProperty->MP / RoleProperty->MaxMP);
	return RoleProperty->MP;
}

void URolePropertyComponent::RecoveryProperty(float DeltaTime)
{
	ChangeHP(DeltaTime * RoleProperty->RecoveryHP);
	ChangeMP(DeltaTime * RoleProperty->RecoveryMP);
}
