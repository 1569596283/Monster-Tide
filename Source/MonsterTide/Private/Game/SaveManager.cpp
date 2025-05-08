// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SaveManager.h"
#include "Game/SaveGameData.h"
#include "Roles/RolePropertyComponent.h"
#include "Kismet/GameplayStatics.h"


void USaveManager::SaveGameData()
{
	UGameplayStatics::SaveGameToSlot(GameData, "TestSaveData", 0);
}

void USaveManager::InitSaveData()
{
	if (GameData != nullptr) {
		GameData->RemoveFromRoot();
	}
	USaveGame* Data = UGameplayStatics::LoadGameFromSlot("TestSaveData", 0);
	//if (Data != nullptr) {
	//	GameData = Cast<USaveGameData>(Data);
	//}
	//else {
	//	GameData = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
	//	FRoleProperty* rp = getRandomRoleProperty(ERoleType::Hero);
	//	GameData->AddHero(rp);
	//}
	GameData = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
	GameData->AddToRoot();
	for (int i = 0; i < 4; i++) {
		FRoleProperty* rp = getRandomRoleProperty(ERoleType::Hero);
		GameData->AddHero(rp);
	}
}

const TArray<FRoleProperty>& USaveManager::GetHeroArray() const
{
	return GameData->GetHeroArray();
}