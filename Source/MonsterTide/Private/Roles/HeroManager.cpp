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

void UHeroManager::RoleUseSkill(ESkillType Type, TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target)
{
	this->OnRoleUseSkill.Broadcast(Type, User, Target);
}
