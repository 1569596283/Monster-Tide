// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/UI_Game.h"
#include "UI/Game/UI_HeroItem.h"
#include "Components/ScrollBox.h"
#include "Roles/HeroManager.h"
#include "Data/RolePropertyData.h"

void UUI_Game::NativeOnInitialized()
{
	RefreshHeros();
}

void UUI_Game::RefreshHeros()
{
	TArray<FRoleProperty>* RPArr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->GetHeroArray();
	for (int i = 0; i < RPArr->Num(); i++) {
		AddHeroItem(RPArr->GetData() + i);
	}
}

void UUI_Game::AddHeroItem(FRoleProperty* rp)
{
	if (ScrHero && HeroItemClass) {
		UUI_HeroItem* item = CreateWidget<UUI_HeroItem>(this, HeroItemClass);
		ScrHero->AddChild(item);
		item->InitRoleProperty(rp);
	}
}
