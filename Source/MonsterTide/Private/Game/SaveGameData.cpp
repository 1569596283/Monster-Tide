// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SaveGameData.h"
#include "Roles/RolePropertyComponent.h"

const TArray< FRoleProperty >& USaveGameData::GetHeroArray() const
{
	return HeroArr;
}

bool USaveGameData::AddHero(FRoleProperty* rp)
{
	HeroArr.Push(*rp);
	return true;
}
