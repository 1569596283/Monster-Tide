// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/UI_LevelItem.h"
#include "Data/LevelData.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Levels/LevelManager.h"
#include "Game/SaveManager.h"

void UUI_LevelItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Btn_Level) {
		Btn_Level->OnClicked.AddDynamic(this, &UUI_LevelItem::OnBtnLevelClicked);
	}
}

void UUI_LevelItem::InitLevelConfig(FLevelConfig* LevelCfg)
{
	int LastLevel = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>()->GetLastLevel(LevelCfg->Type);
	CurLevel = LevelCfg->Level;
	TB_Level->SetText(FText::FromString(FString::FromInt(CurLevel)));
	TB_Name->SetText(FText::FromString(LevelCfg->LevelName));
	Btn_Level->SetIsEnabled(CurLevel <= LastLevel + 1);
}

void UUI_LevelItem::OnBtnLevelClicked()
{
	GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>()->OpenLevel(CurLevel);
}
