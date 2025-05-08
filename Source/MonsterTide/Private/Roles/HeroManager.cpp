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

TArray<FRoleProperty>& UHeroManager::GetHeroArray()
{
	// TODO: 在此处插入 return 语句
	return HeroPropertyArr;
}

void UHeroManager::SelectHeroItem(const FRoleProperty& rp)
{
	if (&rp == CurSelectRoleProperty) {
		CurSelectRoleProperty = nullptr;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("SelectHeroItem"));
		OnSelectItemChanged.Broadcast(rp);
	}
}
