// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HeroManager.generated.h"

struct FRoleProperty;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectItemChanged, const FRoleProperty&, newRoleProperty);

/**
 *
 */
UCLASS()
class MONSTERTIDE_API UHeroManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitHeroProperty();

	TArray<FRoleProperty>& GetHeroArray();

	UPROPERTY(BlueprintAssignable)
	FOnSelectItemChanged OnSelectItemChanged;

	void SelectHeroItem(const FRoleProperty& rp);

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FRoleProperty> HeroPropertyArr;

	FRoleProperty* CurSelectRoleProperty;
};
