// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/UI_SelectLevel.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/ScrollBox.h"
#include "Game/MainPlayerController.h"
#include "Data/LevelData.h"
#include "UI/Main/UI_LevelItem.h"

void UUI_SelectLevel::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Btn_Return != nullptr) {
		Btn_Return->OnClicked.AddDynamic(this, &UUI_SelectLevel::OnBtnReturnClicked);
	}
	if (Btn_Classic != nullptr) {
		Btn_Classic->OnClicked.AddDynamic(this, &UUI_SelectLevel::OnBtnClassicClicked);
	}
	CP_Level->SetVisibility(ESlateVisibility::Collapsed);
	CP_Mode->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UUI_SelectLevel::OnBtnReturnClicked()
{
	if (CP_Level->IsVisible() ) {
		CP_Level->SetVisibility(ESlateVisibility::Collapsed);
		CP_Mode->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else {
		APlayerController* PC = GetOwningPlayer();
		if (!PC) return;
		if (AMainPlayerController* MainPC = Cast<AMainPlayerController>(PC) ){
			MainPC->CloseLevelUMG();
		}
	}
}

void UUI_SelectLevel::OnBtnClassicClicked()
{
	CP_Mode->SetVisibility(ESlateVisibility::Collapsed);
	CP_Level->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	SetScrollLevelByType(ELevelType::Classic);
}

void UUI_SelectLevel::SetScrollLevelByType(ELevelType Type)
{
	TArray<FLevelConfig*>CfgArr = GetLevelConfigs(Type);
	for (int i = 0; i < LevelItemArr.Num();i++) {
		UUI_LevelItem* Item = LevelItemArr[i];
		if (CfgArr.Num() > i ) {
			Item->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			Item->InitLevelConfig(CfgArr[i]);
		}
		else {
			Item->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	for (int i = LevelItemArr.Num(); i < CfgArr.Num();i++) {
		if (SB_Level && LevelItemClass) {
			UUI_LevelItem* Item = CreateWidget<UUI_LevelItem>(this, LevelItemClass);
			SB_Level->AddChild(Item);
			Item->InitLevelConfig(CfgArr[i]);
		}
	}
}
