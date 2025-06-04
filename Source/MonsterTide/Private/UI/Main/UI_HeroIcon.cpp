// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/UI_HeroIcon.h"
#include "Roles/RoleAttribute.h"
#include "Components/Button.h"

void UUI_HeroIcon::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Btn_Hero != nullptr) {
		Btn_Hero->OnClicked.AddDynamic(this, &UUI_HeroIcon::OnBtnHeroIconClicked);
	}
}

void UUI_HeroIcon::InitAttribute(TObjectPtr<URoleAttribute> Attribute)
{
	RoleAttribute = Attribute;
}

void UUI_HeroIcon::SetState(bool Select)
{
	FButtonStyle BtnStyle = Btn_Hero->GetStyle();
	// ÉèÖÃÆÕÍ¨×´Ì¬ÑÕÉ«
	if (Select) {
		BtnStyle.Normal.TintColor = FSlateColor(FLinearColor::Green);
	}
	else {
		BtnStyle.Normal.TintColor = FSlateColor(FLinearColor::Gray);
	}
	Btn_Hero->SetStyle(BtnStyle);
}

void UUI_HeroIcon::OnBtnHeroIconClicked()
{
	OnHeroIconClicked.Broadcast(RoleAttribute);
}
