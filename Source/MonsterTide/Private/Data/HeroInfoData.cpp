// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/HeroInfoData.h"
#include "Data/RolePropertyData.h"


FHeroInfo::FHeroInfo()
{

}

FHeroInfo GetRandomHeroInfo(FString ID, ERoleType Type, int Level)
{
	FHeroInfo HeroInfo = FHeroInfo();
	HeroInfo.ID = ID;
	HeroInfo.Type = Type;
	HeroInfo.Level = Level;
	HeroInfo.Exp = 0.f;
	HeroInfo.Name = "Hero" + ID;
	if (Level > 1) {
		FRoleProperty* BaseProperty = GetRandomHeroProperty(Type);
		HeroInfo.BaseRoleProperty = *GetTargetLevelProperty(BaseProperty, 1, Level);
	}
	else
	{
		HeroInfo.BaseRoleProperty = *GetRandomHeroProperty(Type);
	}
	return HeroInfo;
}
