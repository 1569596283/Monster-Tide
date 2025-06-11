// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/HeroManager.h"
#include "Roles/Heros/HeroBase.h"
#include "Roles/RoleAttribute.h"
#include "Game/SaveManager.h"
#include "Data/RolePropertyData.h"
#include "Data/HeroInfoData.h"

void UHeroManager::InitHeroProperty()
{
	TArray<FHeroInfo> RPArr = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>()->GetHeroInfoArray();
	for (int i = 0; i < RPArr.Num(); i++) {
		TObjectPtr< URoleAttribute > RA = NewObject<URoleAttribute>();
		FHeroInfo HeroInfo = RPArr[i];
		RA->SetBaseProperty(HeroInfo.BaseRoleProperty);
		HeroMap.Add(RA, HeroInfo.ID);
	}
}

FHeroInfo UHeroManager::AddRandomHero()
{
	ERoleType Type = GetRandomHeroType();
	FHeroInfo HeroInfo = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>()->AddRandomHero(Type, 1);
	TObjectPtr< URoleAttribute > RA = NewObject<URoleAttribute>();
	RA->SetBaseProperty(HeroInfo.BaseRoleProperty);
	HeroMap.Add(RA, HeroInfo.ID);
	return HeroInfo;
}

void UHeroManager::AddBattleHero(TObjectPtr<URoleAttribute> RoleAttribute)
{
	BattleHeroAttributeArr.Push(RoleAttribute);
	FHeroInfo HeroInfo = GetHeroInfo(RoleAttribute);
	BattleHeroInfoArr.Push(HeroInfo);
}

void UHeroManager::RemoveBattleHero(TObjectPtr<URoleAttribute> RoleAttribute)
{
	for (int i = 0; i < BattleHeroAttributeArr.Num(); i++) {
		if (BattleHeroAttributeArr[i] == RoleAttribute) {
			BattleHeroAttributeArr.RemoveAt(i);
			break;
		}
	}
	FString ID = *HeroMap.Find(RoleAttribute);
	for (int i = 0; i < BattleHeroInfoArr.Num(); i++) {
		if (BattleHeroInfoArr[i].ID == ID) {
			BattleHeroInfoArr.RemoveAt(i);
			break;
		}
	}
}

TArray<TObjectPtr<URoleAttribute>> UHeroManager::GetBattleHeroAttributeArray()
{
	return BattleHeroAttributeArr;
}

TArray<TObjectPtr<URoleAttribute>> UHeroManager::GetAllHeroAttributeArray()
{
	TArray<TObjectPtr<URoleAttribute>> AttributeArray;
	// 遍历键值对
	for (const TPair<TObjectPtr<URoleAttribute>, FString>& Pair : HeroMap)
	{
		AttributeArray.Push(Pair.Key);
	}
	return AttributeArray;
}

TArray<FHeroInfo> UHeroManager::GetBattleHeroInfoArr()
{
	return BattleHeroInfoArr;
}

int UHeroManager::GetBattleHeroNumber() const
{
	return BattleHeroInfoArr.Num();
}

FHeroInfo UHeroManager::GetHeroInfo(TObjectPtr<URoleAttribute> Attribute)
{
	FString ID = *HeroMap.Find(Attribute);
	FHeroInfo HeroInfo = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>()->GetHeroInfo(ID);
	return HeroInfo;
}

FHeroInfo UHeroManager::GetBattleHeroInfo(TObjectPtr<URoleAttribute> Attribute)
{
	FString ID = *HeroMap.Find(Attribute);
	for (auto& HeroInfo : BattleHeroInfoArr) {
		if (ID == HeroInfo.ID) {
			return HeroInfo;
		}
	}
	return FHeroInfo();
}

FString UHeroManager::ChangeHeroName(TObjectPtr<URoleAttribute> Attribute, FString NewName)
{
	FString ID = *HeroMap.Find(Attribute);
	return  GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>()->ChangeHeroName(ID, NewName);
}

void UHeroManager::SelectHeroItem(TObjectPtr< URoleAttribute > RA)
{
	if (RA == CurSelectRoleAttribute) {
		CurSelectRoleAttribute = nullptr;
	}
	else {
		CurSelectRoleAttribute = RA;
	}
}

TObjectPtr<URoleAttribute> UHeroManager::GetCurSelectHero() const
{
	return CurSelectRoleAttribute;
}

void UHeroManager::CreateHeroAtLocation(FVector loc)
{
	if (CurSelectRoleAttribute == nullptr) {
		return;
	}
	FVector SpawnLocation(loc.X, loc.Y, loc.Z + 200); // 生成位置
	FRotator SpawnRotation(0, 0, 0);  // 生成旋转
	FHeroInfo HeroInfo = GetBattleHeroInfo(CurSelectRoleAttribute);
	FHeroPropertyConfig* HeroPropertyConfig = GetHeroPropertyConfig(HeroInfo.Type);
	TSubclassOf<AHeroBase> HeroClass = HeroPropertyConfig->HeroClass;
	if (HeroClass) {
		AHeroBase* Hero = GetWorld()->SpawnActor<AHeroBase>(HeroClass, SpawnLocation, SpawnRotation);
		Hero->InitRole(HeroInfo.Level, CurSelectRoleAttribute);
		Hero->OnRoleUseSkill.AddUObject(this, &UHeroManager::RoleUseSkill);
		OnHeroAddExp.AddUObject(Hero, &AHeroBase::RefreshProperty);
	}
	OnPlaceHero.Broadcast(CurSelectRoleAttribute);
	CurSelectRoleAttribute = nullptr;
}

void UHeroManager::AddExp(TObjectPtr<ARoleBase> Killer, float Exp)
{
	for (int i = 0; i < BattleHeroAttributeArr.Num(); i++) {
		TObjectPtr< URoleAttribute > RA = BattleHeroAttributeArr[i];
		if (IsValid(RA) && !RA->IsDead()) {
			// HeroAddExp 会改变BattleHeroInfoArr[i]的值
			int CurLevel = BattleHeroInfoArr[i].Level;
			int AddLevel = CurLevel;
			if (RA->GetRoleProperty() == Killer->GetRoleProperty()) {
				AddLevel = HeroAddExp(i, Exp);
			}
			else {
				AddLevel = HeroAddExp(i, Exp * 0.3f);
			}
			FHeroInfo HeroInfo = BattleHeroInfoArr[i];
			OnHeroAddExp.Broadcast(RA, AddLevel, HeroInfo.Exp);
			if (CurLevel != AddLevel) {
				RA->AddLevel(CurLevel, AddLevel);
			}
		}
	}
}

void UHeroManager::EnterBattle()
{
	RecoverTime = 0.1f;
	GetWorld()->GetTimerManager().SetTimer(BattleTimerHandle, this, &UHeroManager::RecoverHeros, RecoverTime, true);
}

void UHeroManager::ExitBattle()
{
	OnPlaceHero.Clear();
	OnRoleUseSkill.Clear();
	OnHeroAddExp.Clear();
	GetWorld()->GetTimerManager().ClearTimer(BattleTimerHandle);
	RecoverHerosAllStatuses();
}

void UHeroManager::RoleUseSkill(ESkillType Type, float Damage, TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target)
{
	this->OnRoleUseSkill.Broadcast(Type, Damage, User, Target);
}

void UHeroManager::RecoverHerosAllStatuses()
{
	for (int i = 0; i < BattleHeroAttributeArr.Num(); i++) {
		BattleHeroAttributeArr[i]->RecoveryAllStatuses();
	}
}

int UHeroManager::HeroAddExp(int Index, float Exp)
{
	FHeroInfo HeroInfo = BattleHeroInfoArr[Index];
	HeroInfo.Exp += Exp;
	int TargetExp = 100 * HeroInfo.Level;
	while (HeroInfo.Exp >= TargetExp) {
		HeroInfo.Level++;
		HeroInfo.Exp -= TargetExp;
	}
	BattleHeroInfoArr[Index] = HeroInfo;
	return HeroInfo.Level;
}

void UHeroManager::RecoverHeros()
{
	for (int i = 0; i < BattleHeroAttributeArr.Num(); i++) {
		BattleHeroAttributeArr[i]->RecoveryProperty(RecoverTime);
	}
}
