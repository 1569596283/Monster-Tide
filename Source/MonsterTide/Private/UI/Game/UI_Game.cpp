// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/UI_Game.h"
#include "UI/Game/UI_HeroItem.h"
#include "Components/ScrollBox.h"
#include "Roles/RolePropertyComponent.h"
#include <Game/SaveManager.h>

void UUI_Game::NativeOnInitialized()
{
	GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>()->InitSaveData();
	RefreshHeros();
}

void UUI_Game::RefreshHeros()
{
	const TArray<FRoleProperty>& RPArr = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>()->GetHeroArray();
	for (int i = 0; i < RPArr.Num(); i++) {
		AddHeroItem(RPArr[i]);
	}
}

void UUI_Game::AddHeroItem(const FRoleProperty& rp)
{
	if (ScrHero && HeroItemClass) {
		UUI_HeroItem* item = CreateWidget<UUI_HeroItem>(this, HeroItemClass);
		ScrHero->AddChild(item);
	}
}
