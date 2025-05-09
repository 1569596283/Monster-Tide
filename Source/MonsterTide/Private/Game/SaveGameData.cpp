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
