// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "RolePropertyComponent.generated.h"

struct FRoleProperty;
class UUI_RoleProperty;
class URoleAttribute;

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class MONSTERTIDE_API URolePropertyComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	bool InitProperty(int Level, const TObjectPtr<URoleAttribute> RA);

	UFUNCTION()
	void RefreshProperty();

	void RefreshLevel(int Level);

	TObjectPtr<UUI_RoleProperty> UMG_RoleProperty;

	UFUNCTION()
	void RefreshHP();
	UFUNCTION()
	void RefreshMP();

protected:
	const FRoleProperty* RoleProperty;

private:

};
