// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/UI_HeroIcon.h"
#include "Roles/RoleAttribute.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Data/HeroInfoData.h"
#include "Roles/HeroManager.h"

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
	FHeroInfo HeroInfo = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->GetHeroInfo(Attribute);
	TB_Name ->SetText(FText::FromString(HeroInfo.Name)) ;
	TB_Level->SetText(FText::FromString(FString::FromInt(HeroInfo.Level)));
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
