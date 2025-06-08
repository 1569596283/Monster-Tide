// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/UI_HeroItem.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Roles/HeroManager.h"
#include "Roles/RoleAttribute.h"
#include "Data/RolePropertyData.h"
#include "Data/HeroInfoData.h"

void UUI_HeroItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Btn_Hero != nullptr) {
		Btn_Hero->OnClicked.AddDynamic(this, &UUI_HeroItem::OnBtnHeroClicked);
		auto mgr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>();
		mgr->OnSelectItemChanged.AddUObject(this, &UUI_HeroItem::SetBtnHeroState);
		mgr->OnPlaceHero.AddUObject(this, &UUI_HeroItem::OnPlaceHero);
	}
}

void UUI_HeroItem::InitRoleAttribute(TObjectPtr< URoleAttribute > RA)
{
	RoleAttribute = RA;
	const FRoleProperty* RoleProperty = RA->GetRoleProperty();
	auto mgr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>();
	FHeroInfo HeroInfo = mgr->GetBattleHeroInfo(RA);
	mgr->OnHeroAddExp.AddUObject(this, &UUI_HeroItem::RefreshLevel);
	TB_Name->SetText(FText::FromString(HeroInfo.Name));
	TB_Type->SetText(UEnum::GetDisplayValueAsText(HeroInfo.Type));
	TB_Level->SetText(FText::FromString(FString::FromInt(HeroInfo.Level)));
	FString EXPText = FString::FromInt(HeroInfo.Exp) + "/" + FString::FromInt(100 * HeroInfo.Level);
	TB_EXP->SetText(FText::FromString(EXPText));
	PB_EXP->SetPercent(HeroInfo.Exp / 100 * HeroInfo.Level);

	FString HPText = FString::FromInt(RoleProperty->HP) + "/" + FString::FromInt(RoleProperty->MaxHP);
	TB_HP->SetText(FText::FromString(HPText));
	PB_HP->SetPercent(RoleProperty->HP / RoleProperty->MaxHP);
	FString MPText = FString::FromInt(RoleProperty->MP) + "/" + FString::FromInt(RoleProperty->MaxMP);
	TB_MP->SetText(FText::FromString(MPText));
	PB_MP->SetPercent(RoleProperty->MP / RoleProperty->MaxMP);

}

void UUI_HeroItem::OnBtnHeroClicked()
{
	if (IsSelect) {
		SetBtnHeroState(RoleAttribute);
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->SelectHeroItem(RoleAttribute);
}

void UUI_HeroItem::RefreshLevel(TObjectPtr< URoleAttribute > Attribute, int Level, float Exp)
{
	if (RoleAttribute == Attribute) {
		TB_Level->SetText(FText::FromString(FString::FromInt(Level)));
		FString EXPText = FString::FromInt(Exp) + "/" + FString::FromInt(100 * Level);
		TB_EXP->SetText(FText::FromString(EXPText));
		PB_EXP->SetPercent(Exp / 100 * Level);
	}
}

void UUI_HeroItem::SetBtnHeroState(TObjectPtr< URoleAttribute > RA)
{
	bool newState = false;
	if (!IsSelect && RA == RoleAttribute) {
		// 改为选中状态
		newState = true;
	}
	else if ((IsSelect && RA == RoleAttribute) || IsSelect && RA != RoleAttribute) {
		newState = false;
	}
	if (newState != IsSelect) {
		IsSelect = newState;
		RefreshBtnHeroState();
	}
}

void UUI_HeroItem::RefreshBtnHeroState()
{
	FButtonStyle BtnStyle = Btn_Hero->GetStyle();
	// 设置普通状态颜色
	if (IsSelect) {
		BtnStyle.Normal.TintColor = FSlateColor(FLinearColor::Green);
	}
	else {
		BtnStyle.Normal.TintColor = FSlateColor(FLinearColor::Gray);
	}
	Btn_Hero->SetStyle(BtnStyle);
}

void UUI_HeroItem::OnPlaceHero(TObjectPtr< URoleAttribute > RA)
{
	if (RA == RoleAttribute) {
		RemoveFromParent();
	}
}
