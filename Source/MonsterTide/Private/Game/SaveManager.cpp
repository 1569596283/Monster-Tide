// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SaveManager.h"
#include "Game/SaveGameData.h"
#include "Data/RolePropertyData.h"
#include "Kismet/GameplayStatics.h"


void USaveManager::SaveGameData(FString Name)
{
	UGameplayStatics::SaveGameToSlot(GameData, Name, 0);
}

void USaveManager::InitSaveData()
{
	GameData = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
	FRoleProperty* rp_1 = GetRandomHeroProperty(ERoleType::Hero_1);
	GameData->AddHero(rp_1);
	FRoleProperty* rp_2 = GetRandomHeroProperty(ERoleType::Hero_2);
	GameData->AddHero(rp_2);
	FRoleProperty* rp_3 = GetRandomHeroProperty(ERoleType::Hero_3);
	GameData->AddHero(rp_3);
	FRoleProperty* rp_4 = GetRandomHeroProperty(ERoleType::Hero_4);
	GameData->AddHero(rp_4);
}

bool USaveManager::ReadSaveData(FString Name)
{
	USaveGame* Data = UGameplayStatics::LoadGameFromSlot(Name, 0);
	if (Data != nullptr) {
		GameData = Cast<USaveGameData>(Data);
		return true;
	}
	return false;
}

const TArray<FRoleProperty>& USaveManager::GetHeroArray() const
{
	return GameData->GetHeroArray();
}

int USaveManager::GetLastLevel(ELevelType Type)
{
	return GameData->GetLastLevel(Type);
}


void USaveManager::SetLastLevel(ELevelType Type, int Level)
{
	GameData->SetLastLevl(Type, Level);
}

void USaveManager::SetHeroProperty(TArray<FRoleProperty>* RolePropertyArr)
{
	GameData->SetHeroProperty(RolePropertyArr);
}