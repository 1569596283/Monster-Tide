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
		mgr->OnSelectItemChanged.AddDynamic(this, &UUI_HeroItem::SetBtnHeroState);
	}
}

void UUI_HeroItem::InitRoleProperty(FRoleProperty& rp)
{
	RoleProperty = &rp;
	TB_Name->SetText(FText::FromString(TEXT("Name")));
	TB_Type->SetText(UEnum::GetDisplayValueAsText(rp.Type));
	TB_Level->SetText(FText::FromString(FString::FromInt(rp.Level)));
	FString HPText = FString::FromInt(rp.HP) + "/" + FString::FromInt(rp.MaxHP);
	TB_HP->SetText(FText::FromString(HPText));
	PB_HP->SetPercent(rp.HP / rp.MaxHP);
	FString MPText = FString::FromInt(rp.MP) + "/" + FString::FromInt(rp.MaxMP);
	TB_MP->SetText(FText::FromString(MPText));
	PB_MP->SetPercent(rp.MP / rp.MaxMP);
	FString EXPText = FString::FromInt(rp.Exp) + "/" + FString::FromInt(100);
	TB_EXP->SetText(FText::FromString(EXPText));
	PB_EXP->SetPercent(rp.Exp / 100);
}

void UUI_HeroItem::OnBtnHeroClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("OnBtnHeroClicked"));
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->SelectHeroItem(*RoleProperty);
	if (IsSelect) {
		SetBtnHeroState(*RoleProperty);
	}
}

void UUI_HeroItem::SetBtnHeroState(const FRoleProperty& rp)
{
	bool newState = &rp == RoleProperty;
	UE_LOG(LogTemp, Warning, TEXT("SetBtnHeroState newState %d"), newState);
	if (!IsSelect && &rp == RoleProperty) {
		// 改为选中状态
		newState = true;
	}
	else if ((IsSelect && &rp == RoleProperty) || IsSelect && &rp != RoleProperty) {
		newState = false;
	}
	if (newState != IsSelect) {
		IsSelect = newState;
		RefreshBtnHeroState();
	}
	UE_LOG(LogTemp, Warning, TEXT("SetBtnHeroState %d"), IsSelect);
}

void UUI_HeroItem::RefreshBtnHeroState()
{
	UE_LOG(LogTemp, Warning, TEXT("RefreshBtnHeroState %d"), IsSelect);
	//FButtonStyle ButtonStyle = Btn_Hero->GetStyle();
	//if (IsSelect) {
	//	ButtonStyle.SetNormal(FSlateColorBrush(FColor::Green));
	//}
	//else {
	//	ButtonStyle.SetNormal(FSlateColorBrush(FColor::Green));
	//}
	//Btn_Hero->SetStyle(ButtonStyle);
}
