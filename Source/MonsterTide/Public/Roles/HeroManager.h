// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HeroManager.generated.h"

struct FRoleProperty;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectItemChanged, FRoleProperty*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaceHero, FRoleProperty*);

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
	FOnPlaceHero OnPlaceHero;

	void SelectHeroItem(FRoleProperty* rp);

	/* 创建英雄在指定位置 */
	void CreateHeroAtLocation(FVector loc);

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FRoleProperty> HeroPropertyArr;

	FRoleProperty* CurSelectRoleProperty;
};
