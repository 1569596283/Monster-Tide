// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HeroManager.generated.h"

enum class ESkillType :uint8;
struct FRoleProperty;
struct FHeroInfo;
class ARoleBase;
class URoleAttribute;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaceHero, TObjectPtr< URoleAttribute >);
DECLARE_MULTICAST_DELEGATE_FourParams(FOnRoleUseSkill, ESkillType, float, TObjectPtr<ARoleBase>, TObjectPtr<ARoleBase>);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnHeroAddExp, TObjectPtr< URoleAttribute >, int, float);


/**
 *
 */
UCLASS()
class MONSTERTIDE_API UHeroManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void InitHeroProperty();
	FHeroInfo AddRandomHero();
	void AddBattleHero(TObjectPtr< URoleAttribute > RoleAttribute);
	void RemoveBattleHero(TObjectPtr< URoleAttribute > RoleAttribute);

	TArray<TObjectPtr< URoleAttribute >> GetBattleHeroAttributeArray();
	TArray<TObjectPtr< URoleAttribute >> GetAllHeroAttributeArray();
	TArray<FHeroInfo> GetBattleHeroInfoArr();
	int GetBattleHeroNumber() const;
	FHeroInfo GetHeroInfo(TObjectPtr<URoleAttribute> Attribute);
	FHeroInfo GetBattleHeroInfo(TObjectPtr<URoleAttribute> Attribute);
	FString ChangeHeroName(TObjectPtr<URoleAttribute> Attribute, FString NewName);

	FOnPlaceHero OnPlaceHero;
	FOnRoleUseSkill OnRoleUseSkill;
	FOnHeroAddExp OnHeroAddExp;

	void SelectHeroItem(TObjectPtr< URoleAttribute > RA);
	TObjectPtr< URoleAttribute > GetCurSelectHero() const;

	/* 创建英雄在指定位置 */
	void CreateHeroAtLocation(FVector loc);

	void AddExp(TObjectPtr<ARoleBase> Killer, float Exp);

	void EnterBattle();
	void ExitBattle();
	FTimerHandle BattleTimerHandle = FTimerHandle();

	void ClearHero();

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray <TObjectPtr< URoleAttribute >> BattleHeroAttributeArr;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHeroInfo> BattleHeroInfoArr;

	UPROPERTY(BlueprintReadOnly)
	TMap<TObjectPtr<URoleAttribute>, FString > HeroMap;

	TObjectPtr< URoleAttribute > CurSelectRoleAttribute;

	void RoleUseSkill(ESkillType Type, float Damage, TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target);

	void RecoverHerosAllStatuses();

	int HeroAddExp(int Index, float Exp);

	UFUNCTION()
	void RecoverHeros();
	UPROPERTY()
	float RecoverTime = 0.1f;
};
