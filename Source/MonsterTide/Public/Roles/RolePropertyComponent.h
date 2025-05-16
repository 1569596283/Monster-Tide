// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "RolePropertyComponent.generated.h"

struct FRoleProperty;
class UUI_RoleProperty;

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class MONSTERTIDE_API URolePropertyComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	bool InitProperty(FRoleProperty* rp);
	void RefreshProperty();

	TObjectPtr<UUI_RoleProperty> UMG_RoleProperty;

	const FRoleProperty* GetRoleProperty();

	bool IsDead();

	float ChangeHP(float Value);
	float ChangeMP(float Value);

protected:
	FRoleProperty* RoleProperty;
};
