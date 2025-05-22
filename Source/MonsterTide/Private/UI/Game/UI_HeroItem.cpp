// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/UI_HeroItem.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Roles/HeroManager.h"
#include "Roles/RoleAttribute.h"
#include "Data/RolePropertyData.h"

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
	TB_Name->SetText(FText::FromString(TEXT("Name")));
	TB_Type->SetText(UEnum::GetDisplayValueAsText(RoleProperty->Type));
	TB_Level->SetText(FText::FromString(FString::FromInt(RoleProperty->Level)));
	FString HPText = FString::FromInt(RoleProperty->HP) + "/" + FString::FromInt(RoleProperty->MaxHP);
	TB_HP->SetText(FText::FromString(HPText));
	PB_HP->SetPercent(RoleProperty->HP / RoleProperty->MaxHP);
	FString MPText = FString::FromInt(RoleProperty->MP) + "/" + FString::FromInt(RoleProperty->MaxMP);
	TB_MP->SetText(FText::FromString(MPText));
	PB_MP->SetPercent(RoleProperty->MP / RoleProperty->MaxMP);
	FString EXPText = FString::FromInt(RoleProperty->Exp) + "/" + FString::FromInt(100);
	TB_EXP->SetText(FText::FromString(EXPText));
	PB_EXP->SetPercent(RoleProperty->Exp / 100);
}

void UUI_HeroItem::OnBtnHeroClicked()
{
	if (IsSelect) {
		SetBtnHeroState(RoleAttribute);
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->SelectHeroItem(RoleAttribute);
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
