// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/UI_LevelItem.h"
#include "Data/LevelData.h"
#include "Components/Button.h"
#include "Levels/LevelManager.h"

void UUI_LevelItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Btn_Level) {
		Btn_Level->OnClicked.AddDynamic(this, &UUI_LevelItem::OnBtnLevelClicked);
	}
}

void UUI_LevelItem::InitLevelConfig(FLevelConfig* LevelCfg)
{
	CurLevel = LevelCfg->Level;
}

void UUI_LevelItem::OnBtnLevelClicked()
{
	GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>()->OpenLevel(CurLevel);
}
