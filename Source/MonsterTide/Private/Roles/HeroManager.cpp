// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/HeroManager.h"
#include "Roles/Heros/HeroBase.h"
#include "Game/SaveManager.h"
#include "Data/RolePropertyData.h"

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
	// TODO: 在此处插入 return 语句
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

void UHeroManager::CreateHeroAtLocation(FVector loc)
{
	if (CurSelectRoleProperty == nullptr) {
		return;
	}
	FVector SpawnLocation(loc.X, loc.Y, loc.Z + 200); // 生成位置
	FRotator SpawnRotation(0, 0, 0);  // 生成旋转
	TSubclassOf<AHeroBase> HeroClass = GetHeroSubclass(CurSelectRoleProperty->Type);
	if (HeroClass) {
		AHeroBase* Hero = GetWorld()->SpawnActor<AHeroBase>(HeroClass, SpawnLocation, SpawnRotation);
		Hero->InitRole(CurSelectRoleProperty);
	}
	OnPlaceHero.Broadcast(CurSelectRoleProperty);
	CurSelectRoleProperty = nullptr;
}
