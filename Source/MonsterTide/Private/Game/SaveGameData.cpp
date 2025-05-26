// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SaveGameData.h"
#include "Data/RolePropertyData.h"

const TArray< FRoleProperty >& USaveGameData::GetHeroArray() const
{
	return HeroArr;
}

bool USaveGameData::AddHero(FRoleProperty* rp)
{
	if (rp) {
		HeroArr.Push(*rp);
		return true;
	}
	else {
		return false;
	}
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

void USaveGameData::SetHeroProperty(TArray<FRoleProperty>* RolePropertyArr)
{
	HeroArr.Empty();
	for (int i = 0; i < RolePropertyArr->Num(); i++) {
		HeroArr.Push(*(RolePropertyArr->GetData() + i));
	}
}