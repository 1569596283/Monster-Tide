// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/UI_Game.h"
#include "UI/Game/UI_HeroItem.h"
#include "Components/ScrollBox.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Components/PanelWidget.h"
#include "Roles/HeroManager.h"
#include "Roles/RoleAttribute.h"
#include "Levels/LevelManager.h"
#include "Data/LevelData.h"
#include "Utils/MyUtils.h"

void UUI_Game::NativeOnInitialized()
{
	if (Btn_SHSelect != nullptr) {
		Btn_SHSelect->OnClicked.AddDynamic(this, &UUI_Game::OnBtnSHSelectClicked);
	}
	if (Btn_Start) {
		Btn_Start->OnClicked.AddDynamic(this, &UUI_Game::OnBtnStartClicked);
	}

	PB_Enemy->SetPercent(0.f);
	ShowAllHeros();
	RefreshHeroCount();
}

void UUI_Game::InitGameUI()
{
	auto LevelMgr = GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>();
	TB_Name->SetText(FText::FromString(LevelMgr->CurLevelConfig.LevelName));
	TB_Time->SetText(FText::FromString(UMyUtils::ConvertSecondsToMinutesSeconds(0.f)));
	FString HP = FString::FromInt(LevelMgr->CurLevelConfig.HP) + "/" + FString::FromInt(LevelMgr->CurLevelConfig.HP);
	TB_HP->SetText(FText::FromString(HP));
	TB_Revenue->SetText(FText::FromString(FString::FromInt(LevelMgr->CurLevelConfig.FairyStone)));

	LevelMgr->OnTimeAdd.AddUObject(this, &UUI_Game::RefreshTime);
	LevelMgr->OnHPChanged.AddUObject(this, &UUI_Game::RefreshHP);
}

void UUI_Game::RefreshEnemyProperss(float Percent)
{
	PB_Enemy->SetPercent(Percent);
}

void UUI_Game::OnBtnSHSelectClicked()
{
	if (CP_Heros->IsVisible()) {
		CP_Heros->SetVisibility(ESlateVisibility::Hidden);
		TB_ShowHide->SetText(FText::FromString(TEXT("显示")));
	}
	else {
		CP_Heros->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		TB_ShowHide->SetText(FText::FromString(TEXT("隐藏")));
	}
}

void UUI_Game::OnBtnStartClicked()
{
	auto LevelMgr = GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>();
	int LevelNum = LevelMgr->GetBattleHeroNumber();
	int SelectNum = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->GetBattleHeroNumber();
	if (SelectNum > 0 && SelectNum <= LevelNum) {
		CP_SelectHeros->SetVisibility(ESlateVisibility::Collapsed);
		InitHeroItems();
		LevelMgr->LevelStart();
	}
}

void UUI_Game::InitHeroItems()
{
	auto HeroMgr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>();
	for (auto& HeroItem : SelectHeroItemArr) {
		HeroItem->Btn_Hero->SetIsEnabled(true);
		HeroItem->OnHeroButtonClicked.AddUObject(this, &UUI_Game::OnHeroSelect);
		HeroMgr->OnPlaceHero.AddUObject(HeroItem, &UUI_HeroItem::OnPlaceHero);
	}
}

void UUI_Game::OnHeroSelect(TObjectPtr<UUI_HeroItem> Item, TObjectPtr<URoleAttribute> RoleAttribute)
{
	auto HeroMgr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>();
	TObjectPtr<URoleAttribute> CurSelect = HeroMgr->GetCurSelectHero();
	if (CurSelect != nullptr) {
		for (auto& HeroItem : SelectHeroItemArr) {
			if (RoleAttribute == HeroItem->GetRoleAttribute()) {
				HeroItem->RefreshBtnHeroState(false);
				break;
			}
		}
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->SelectHeroItem(RoleAttribute);
}

void UUI_Game::ShowAllHeros()
{
	TArray<TObjectPtr<URoleAttribute>> RAArr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->GetAllHeroAttributeArray();
	if (WB_Heros == nullptr || HeroItemClass == nullptr) {
		return;
	}
	for (int i = 0; i < RAArr.Num(); i++) {
		TObjectPtr<URoleAttribute> RoleAttribute = RAArr[i];
		TObjectPtr<UUI_HeroItem> Item = CreateWidget<UUI_HeroItem>(this, HeroItemClass);
		WB_Heros->AddChild(Item);
		Item->InitRoleAttribute(RoleAttribute);
		Item->OnHeroButtonClicked.AddUObject(this, &UUI_Game::AddHeroItem);
	}
}

void UUI_Game::AddHeroItem(TObjectPtr<UUI_HeroItem> Item, TObjectPtr<URoleAttribute> RoleAttribute)
{
	if (ScrHero == nullptr || HeroItemClass == nullptr) {
		return;
	}
	Item->OnHeroButtonClicked.Clear();
	Item->OnHeroButtonClicked.AddUObject(this, &UUI_Game::RemoveHeroItem);
	TObjectPtr<UUI_HeroItem> HeroItem = CreateWidget<UUI_HeroItem>(this, HeroItemClass);
	ScrHero->AddChild(HeroItem);
	HeroItem->InitRoleAttribute(RoleAttribute);
	HeroItem->Btn_Hero->SetIsEnabled(false);
	SelectHeroItemArr.Push(HeroItem);
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->AddBattleHero(RoleAttribute);
	RefreshHeroCount();
}

void UUI_Game::RemoveHeroItem(TObjectPtr<UUI_HeroItem> Item, TObjectPtr<URoleAttribute> RoleAttribute)
{
	Item->OnHeroButtonClicked.Clear();
	Item->OnHeroButtonClicked.AddUObject(this, &UUI_Game::AddHeroItem);
	for (int i = 0; i < SelectHeroItemArr.Num(); i++) {
		if (SelectHeroItemArr[i]->GetRoleAttribute() == RoleAttribute) {
			SelectHeroItemArr[i]->RemoveFromParent();
			SelectHeroItemArr.RemoveAt(i);
		}
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->RemoveBattleHero(RoleAttribute);
	RefreshHeroCount();
}

void UUI_Game::RefreshHeroCount()
{
	auto LevelMgr = GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>();
	auto HeroMgr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>();
	FString Count = FString::FromInt(HeroMgr->GetBattleHeroNumber()) + "/" + FString::FromInt(LevelMgr->GetBattleHeroNumber());
	TB_HeroCount->SetText(FText::FromString(Count));
}

void UUI_Game::RefreshTime(float Time)
{
	TB_Time->SetText(FText::FromString(UMyUtils::ConvertSecondsToMinutesSeconds(Time)));
}

void UUI_Game::RefreshHP(int HP)
{
	auto LevelMgr = GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>();
	FString HPString = FString::FromInt(HP) + "/" + FString::FromInt(LevelMgr->CurLevelConfig.HP);
	TB_HP->SetText(FText::FromString(HPString));
	HP = FMath::Max(HP, 0);
	int FairyStone = 1.0f * HP / LevelMgr->CurLevelConfig.HP * LevelMgr->CurLevelConfig.FairyStone;
	TB_Revenue->SetText(FText::FromString(FString::FromInt(FairyStone)));
}
