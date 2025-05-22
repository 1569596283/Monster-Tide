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
	/* ʵ������ */
	FRoleProperty* RoleProperty;
	/* �������� */
	FRoleProperty* BaseRoleProperty;
	/* װ������ */
	FRoleProperty* EquipRoleProperty;
	/* BUFF���� */
	FRoleProperty* BUFFRoleProperty;
};
