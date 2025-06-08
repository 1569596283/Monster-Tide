// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SaveGameData.h"
#include "Data/RolePropertyData.h"
#include "Data/HeroInfoData.h"

TArray< FHeroInfo > USaveGameData::GetHeroInfoArray()
{
	return HeroInfoArr;
}

FHeroInfo USaveGameData::GetHeroInfo(FString ID)
{
	for (auto &HeroInfo : HeroInfoArr) {
		if (HeroInfo.ID == ID) {
			return HeroInfo;
		}
	}
	return FHeroInfo();
}

FString USaveGameData::ChangeHeroName(FString ID, FString NewName)
{
	if (NewName.Len() <= 3 || NewName.Len() >= 15) {
		NewName = "Hero";
	}
	for (auto& HeroInfo : HeroInfoArr) {
		if (HeroInfo.ID == ID) {
			HeroInfo.Name = NewName;
			return HeroInfo.Name;
		}
	}
	return "Hero";
}

FHeroInfo* USaveGameData::AddHero(ERoleType Type, int Level)
{
	HeroIndex++;
	FString ID = FString::FromInt(HeroIndex);
	FHeroInfo HeroInfo = GetRandomHeroInfo(ID, Type, Level);
	HeroInfoArr.Push(HeroInfo);
	return &HeroInfoArr.Last();
}

int USaveGameData::GetLastLevel(ELevelType Type)
{
	if (LastLevelMap.Find(Type)) {
		return *LastLevelMap.Find(Type);
	}
	else {
		LastLevelMap.Add(Type, 0);
		return 0;
	}
}


void USaveGameData::SetLastLevl(ELevelType Type, int Level)
{
	if (Level > *LastLevelMap.Find(Type)) {
		LastLevelMap[Type] = Level;
	}
}

void USaveGameData::RefreshHeroInfo(FHeroInfo HeroInfo)
{
	for (int i = 0; i < HeroInfoArr.Num();i++) {
		if (HeroInfoArr[i].ID == HeroInfo.ID) {
			HeroInfoArr[i] = HeroInfo;
		}
	}
}