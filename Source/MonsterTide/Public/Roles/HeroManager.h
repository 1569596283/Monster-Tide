// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HeroManager.generated.h"

enum class ESkillType :uint8;
struct FRoleProperty;
class ARoleBase;
class URoleAttribute;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectItemChanged, TObjectPtr< URoleAttribute >);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaceHero, TObjectPtr< URoleAttribute >);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRoleUseSkill, ESkillType, TObjectPtr<ARoleBase>, TObjectPtr<ARoleBase>);

/**
 *
 */
UCLASS()
class MONSTERTIDE_API UHeroManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitHeroProperty();

	TArray<TObjectPtr< URoleAttribute >> GetHeroAttributeArray();
	TArray<FRoleProperty> GetHeroBasePropertyArray();

	FOnSelectItemChanged OnSelectItemChanged;
	FOnPlaceHero OnPlaceHero;
	FOnRoleUseSkill OnRoleUseSkill;

	void SelectHeroItem(TObjectPtr< URoleAttribute > RA);

	/* 创建英雄在指定位置 */
	void CreateHeroAtLocation(FVector loc);

	void AddExp(TObjectPtr<ARoleBase> Killer , float Exp);

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray <TObjectPtr< URoleAttribute >> HeroAttributeArr;

	TObjectPtr< URoleAttribute > CurSelectRoleAttribute;

	void RoleUseSkill(ESkillType Type, TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target);
};
