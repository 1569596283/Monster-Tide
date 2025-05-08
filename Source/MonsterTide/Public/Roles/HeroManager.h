// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HeroManager.generated.h"

struct FRoleProperty;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectItemChanged, FRoleProperty*);

/**
 *
 */
UCLASS()
class MONSTERTIDE_API UHeroManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitHeroProperty();

	TArray<FRoleProperty>* GetHeroArray();

	FOnSelectItemChanged OnSelectItemChanged;

	void SelectHeroItem(FRoleProperty* rp);

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FRoleProperty> HeroPropertyArr;

	FRoleProperty* CurSelectRoleProperty;
};
