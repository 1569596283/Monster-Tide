// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SaveManager.h"
#include "Game/SaveGameData.h"
#include "Data/RolePropertyData.h"
#include "Data/HeroInfoData.h"
#include "Kismet/GameplayStatics.h"


void USaveManager::SaveGameData(FString Name)
{
	UGameplayStatics::SaveGameToSlot(GameData, Name, 0);
	DataSlotName = Name;
}

void USaveManager::InitSaveData()
{
	GameData = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
	GameData->AddHero(ERoleType::Hero_1, 1);
	GameData->AddHero(ERoleType::Hero_2, 1);
	GameData->AddHero(ERoleType::Hero_3, 1);
	GameData->AddHero(ERoleType::Hero_4, 1);
}

bool USaveManager::ReadSaveData(FString Name)
{
	USaveGame* Data = UGameplayStatics::LoadGameFromSlot(Name, 0);
	if (Data != nullptr) {
		GameData = Cast<USaveGameData>(Data);
		DataSlotName = Name;
		return true;
	}
	return false;
}

TArray<FHeroInfo> USaveManager::GetHeroInfoArray()
{
	return GameData->GetHeroInfoArray();
}

FHeroInfo USaveManager::GetHeroInfo(FString ID)
{
	FHeroInfo HeroInfo = GameData->GetHeroInfo(ID);
	return HeroInfo;
}

FString USaveManager::ChangeHeroName(FString ID, FString NewName)
{
	FHeroInfo HeroInfo = GetHeroInfo(ID);
	if (HeroInfo.Name != NewName) {
		NewName = GameData->ChangeHeroName(ID, NewName);
		SaveGameData(DataSlotName);
	}
	return NewName;
}

int USaveManager::GetFairyStone() const
{
	return GameData->GetFairyStone();
}

bool USaveManager::ChangeFairyStone(int Value)
{
	return GameData->ChangeFairyStone(Value);
}

int USaveManager::GetLastLevel(ELevelType Type)
{
	return GameData->GetLastLevel(Type);
}


void USaveManager::SetLastLevel(ELevelType Type, int Level)
{
	GameData->SetLastLevl(Type, Level);
}

void USaveManager::RefreshHeroInfo(FHeroInfo HeroInfo)
{
	GameData->RefreshHeroInfo(HeroInfo);
}

void USaveManager::RefreshHeroInfo(TArray<FHeroInfo> HeroInfoArr)
{
	for (FHeroInfo& HeroInfo : HeroInfoArr) {
		GameData->RefreshHeroInfo(HeroInfo);
	}
}
