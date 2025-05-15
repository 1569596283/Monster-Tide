// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/UI_RoleProperty.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UUI_RoleProperty::SetLevel(int Level)
{
	TB_Level->SetText(FText::FromString(FString::FromInt(Level)));
}

void UUI_RoleProperty::SetHP(float Percent)
{
	PB_HP->SetPercent(Percent);
}

void UUI_RoleProperty::SetMP(float Percent)
{
	PB_MP->SetPercent(Percent);
}
