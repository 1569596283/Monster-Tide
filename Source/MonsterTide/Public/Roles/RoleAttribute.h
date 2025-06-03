// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RoleAttribute.generated.h"

struct FRoleProperty;

DECLARE_DYNAMIC_DELEGATE(FOnRolePropertyChanged);
DECLARE_DYNAMIC_DELEGATE(FOnRoleHPChanged);
DECLARE_DYNAMIC_DELEGATE(FOnRoleMPChanged);


/**
 * 
 */
UCLASS()
class MONSTERTIDE_API URoleAttribute : public UObject
{
	GENERATED_BODY()

public:
	void SetBaseProperty(const FRoleProperty& RP);

	FOnRolePropertyChanged OnRolePropertyChanged;
	void RefreshRoleProperty();

	const FRoleProperty* GetRoleProperty() const;
	const FRoleProperty* GetBaseProperty() const;

	bool IsDead();

	FOnRoleHPChanged OnRoleHPChanged;
	void ChangeHP(float Value);
	FOnRoleMPChanged OnRoleMPChanged;
	void ChangeMP(float Value);

	void AddExp(float Exp);

	void RecoveryProperty(float Time);
	void RecoveryAllStatuses();

protected:
	/* ʵ������ */
	FRoleProperty* RoleProperty;
	/* �������� */
	FRoleProperty* BaseRoleProperty;
	/* װ������ */
	FRoleProperty* EquipRoleProperty;
	/* BUFF���� */
	FRoleProperty* BUFFRoleProperty;

	void LevelUp(int TargetLevel);
};
