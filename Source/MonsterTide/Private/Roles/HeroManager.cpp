// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/HeroManager.h"
#include "Roles/Heros/HeroBase.h"
#include "Roles/RoleAttribute.h"
#include "Game/SaveManager.h"
#include "Data/RolePropertyData.h"

void UHeroManager::InitHeroProperty()
{
	const TArray<FRoleProperty>& RPArr = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>()->GetHeroArray();
	for (int i = 0; i < RPArr.Num(); i++) {
		TObjectPtr< URoleAttribute > RA = NewObject<URoleAttribute>();
		RA->SetBaseProperty(RPArr[i]);
		HeroAttributeArr.Push(RA);
	}
}

TArray<TObjectPtr<URoleAttribute>> UHeroManager::GetHeroAttributeArray()
{
	return HeroAttributeArr;
}

TArray<FRoleProperty> UHeroManager::GetHeroBasePropertyArray()
{
	TArray<FRoleProperty> HeroBasePropertyArray;
	for (int i = 0; i < HeroAttributeArr.Num(); i++) {
		FRoleProperty RP = *HeroAttributeArr[i]->GetBaseProperty();
		HeroBasePropertyArray.Push(RP);
	}
	return HeroBasePropertyArray;
}

void UHeroManager::SelectHeroItem(TObjectPtr< URoleAttribute > RA)
{
	if (RA == CurSelectRoleAttribute) {
		CurSelectRoleAttribute = nullptr;
	}
	else {
		CurSelectRoleAttribute = RA;
		OnSelectItemChanged.Broadcast(RA);
	}
}

void UHeroManager::CreateHeroAtLocation(FVector loc)
{
	if (CurSelectRoleAttribute == nullptr) {
		return;
	}
	FVector SpawnLocation(loc.X, loc.Y, loc.Z + 200); // 生成位置
	FRotator SpawnRotation(0, 0, 0);  // 生成旋转
	FHeroPropertyConfig* HeroPropertyConfig = GetHeroPropertyConfig(CurSelectRoleAttribute->GetRoleProperty()->Type);
	TSubclassOf<AHeroBase> HeroClass = HeroPropertyConfig->HeroClass;
	if (HeroClass) {
		AHeroBase* Hero = GetWorld()->SpawnActor<AHeroBase>(HeroClass, SpawnLocation, SpawnRotation);
		Hero->InitRole(CurSelectRoleAttribute);
		Hero->OnRoleUseSkill.AddUObject(this, &UHeroManager::RoleUseSkill);
	}
	OnPlaceHero.Broadcast(CurSelectRoleAttribute);
	CurSelectRoleAttribute = nullptr;
}

void UHeroManager::AddExp(TObjectPtr<ARoleBase> Killer, float Exp)
{
	for (int i = 0; i < HeroAttributeArr.Num(); i++) {
		TObjectPtr< URoleAttribute > RA = HeroAttributeArr[i];
		if (IsValid(RA) && !RA->IsDead()) {
			if (RA->GetRoleProperty() == Killer->GetRoleProperty()) {
				RA->AddExp(Exp);
			}
			else {
				RA->AddExp(Exp * 0.3f);
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
	GetWorld()->GetTimerManager().ClearTimer(BattleTimerHandle);
}

void UHeroManager::RoleUseSkill(ESkillType Type, float Damage, TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target)
{
	this->OnRoleUseSkill.Broadcast(Type, Damage, User, Target);
}

void UHeroManager::RecoverHeros()
{
	for (int i = 0; i < HeroAttributeArr.Num(); i++) {
		HeroAttributeArr[i]->RecoveryProperty(RecoverTime);
	}
}
