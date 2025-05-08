// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/HeroManager.h"
#include "Game/SaveManager.h"
#include "Roles/RolePropertyComponent.h"

void UHeroManager::InitHeroProperty()
{
	const TArray<FRoleProperty>& RPArr = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>()->GetHeroArray();
	for (int i = 0; i < RPArr.Num(); i++) {
		FRoleProperty* RP = new FRoleProperty(RPArr[i]);
		HeroPropertyArr.Push(*RP);
	}
}

TArray<FRoleProperty>* UHeroManager::GetHeroArray()
{
	// TODO: �ڴ˴����� return ���
	return &HeroPropertyArr;
}

void UHeroManager::SelectHeroItem(FRoleProperty* rp)
{
	if (rp == CurSelectRoleProperty) {
		CurSelectRoleProperty = nullptr;
	}
	else {
		CurSelectRoleProperty = rp;
		OnSelectItemChanged.Broadcast(rp);
	}
}
