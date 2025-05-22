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
	for (int i = 0; i < 4; i++) {
		FRoleProperty* rp = GetRandomHeroProperty(ERoleType::Hero);
		GameData->AddHero(rp);
	}
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

void USaveManager::SetCurLevel(int Level)
{
	GameData->SetCurLevl(Level);
}

void USaveManager::SetHeroProperty(TArray<FRoleProperty>* RolePropertyArr)
{
	GameData->SetHeroProperty(RolePropertyArr);
}
