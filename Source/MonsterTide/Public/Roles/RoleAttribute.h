// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RoleAttribute.generated.h"

struct FRoleProperty;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API URoleAttribute : public UObject
{
	GENERATED_BODY()

public:
	void SetBaseProperty(const FRoleProperty& RP);

	void RefreshRoleProperty();

	const FRoleProperty* GetRoleProperty() const;

	bool IsDead();

	void ChangeHP(float Value);
	void ChangeMP(float Value);

protected:
	/* 实际属性 */
	FRoleProperty* RoleProperty;
	/* 基础属性 */
	FRoleProperty* BaseRoleProperty;
	/* 装备属性 */
	FRoleProperty* EquipRoleProperty;
	/* BUFF属性 */
	FRoleProperty* BUFFRoleProperty;
};
