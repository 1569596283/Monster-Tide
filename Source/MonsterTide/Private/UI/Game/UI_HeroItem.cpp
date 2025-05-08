// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/UI_HeroItem.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Roles/HeroManager.h"
#include "Roles/RolePropertyComponent.h"

void UUI_HeroItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Btn_Hero != nullptr) {
		Btn_Hero->OnClicked.AddDynamic(this, &UUI_HeroItem::OnBtnHeroClicked);
		auto mgr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>();
		mgr->OnSelectItemChanged.AddUObject(this, &UUI_HeroItem::SetBtnHeroState);
	}
}

void UUI_HeroItem::InitRoleProperty(FRoleProperty* rp)
{
	RoleProperty = rp;
	TB_Name->SetText(FText::FromString(TEXT("Name")));
	TB_Type->SetText(UEnum::GetDisplayValueAsText(rp->Type));
	TB_Level->SetText(FText::FromString(FString::FromInt(rp->Level)));
	FString HPText = FString::FromInt(rp->HP) + "/" + FString::FromInt(rp->MaxHP);
	TB_HP->SetText(FText::FromString(HPText));
	PB_HP->SetPercent(rp->HP / rp->MaxHP);
	FString MPText = FString::FromInt(rp->MP) + "/" + FString::FromInt(rp->MaxMP);
	TB_MP->SetText(FText::FromString(MPText));
	PB_MP->SetPercent(rp->MP / rp->MaxMP);
	FString EXPText = FString::FromInt(rp->Exp) + "/" + FString::FromInt(100);
	TB_EXP->SetText(FText::FromString(EXPText));
	PB_EXP->SetPercent(rp->Exp / 100);
}

void UUI_HeroItem::OnBtnHeroClicked()
{
	if (IsSelect) {
		SetBtnHeroState(RoleProperty);
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->SelectHeroItem(RoleProperty);
}

void UUI_HeroItem::SetBtnHeroState(FRoleProperty* rp)
{
	bool newState = false;
	if (!IsSelect && rp == RoleProperty) {
		// 改为选中状态
		newState = true;
	}
	else if ((IsSelect && rp == RoleProperty) || IsSelect && rp != RoleProperty) {
		newState = false;
	}
	if (newState != IsSelect) {
		IsSelect = newState;
		RefreshBtnHeroState();
	}
}

void UUI_HeroItem::RefreshBtnHeroState()
{
	// 设置普通状态颜色
	if (IsSelect) {
		Btn_Hero->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor::Green);
	}
	else {
		Btn_Hero->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor::Gray);
	}
}
