// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/UI_HeroItem.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Roles/RolePropertyComponent.h"

void UUI_HeroItem::Init(const FRoleProperty& rp)
{
	RoleProperty = rp;
	TB_Name->SetText(FText::FromString(TEXT("Name")));
	TB_Type->SetText(UEnum::GetDisplayValueAsText(rp.Type));
	TB_Level->SetText(FText::FromString(FString::FromInt(rp.Level)));
	FString HPText = FString::FromInt(rp.HP) + "/" + FString::FromInt(rp.MaxHP);
	TB_HP->SetText(FText::FromString(HPText));
	PB_HP->SetPercent(rp.HP / rp.MaxHP);
	FString MPText = FString::FromInt(rp.MP) + "/" + FString::FromInt(rp.MaxMP);
	TB_MP->SetText(FText::FromString(MPText));
	PB_MP->SetPercent(rp.MP / rp.MaxMP);
	FString EXPText = FString::FromInt(rp.Exp) + "/" + FString::FromInt(100);
	TB_EXP->SetText(FText::FromString(EXPText));
	PB_EXP->SetPercent(rp.Exp / 100);
}
