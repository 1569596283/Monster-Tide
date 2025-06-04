// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/UI_Hero.h"
#include "UI/Main/UI_HeroIcon.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Game/MainPlayerController.h"
#include "Roles/HeroManager.h"
#include "Roles/RoleAttribute.h"
#include "Data/RolePropertyData.h"


void UUI_Hero::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Btn_Return != nullptr) {
		Btn_Return->OnClicked.AddDynamic(this, &UUI_Hero::OnBtnReturnClicked);
	}
	ShowHeros();
}

void UUI_Hero::OnBtnReturnClicked()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;
	if (AMainPlayerController* MainPC = Cast<AMainPlayerController>(PC)) {
		MainPC->CloseHeroUMG();
	}
}

void UUI_Hero::ShowHeros()
{
	if (!WB_Heros || !HeroIconClass) {
		return;
	}
	auto HeroMgr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>();
	TArray<TObjectPtr<URoleAttribute>> Heros = HeroMgr->GetHeroAttributeArray();
	for (int i = 0; i < Heros.Num(); i++) {
		TObjectPtr<URoleAttribute> RoleAttribute = Heros[i];
		TObjectPtr<UUI_HeroIcon> Icon = CreateWidget<UUI_HeroIcon>(this, HeroIconClass);
		WB_Heros->AddChild(Icon);
		Icon->InitAttribute(RoleAttribute);
		Icon->OnHeroIconClicked.AddUObject(this, &UUI_Hero::RefreshHeroInfo);
		HeroIconArr.Push(Icon);
	}
	RefreshHeroInfo(Heros[0]);
}

void UUI_Hero::RefreshHeroInfo(TObjectPtr<URoleAttribute> Attribute)
{
	TB_Name->SetText(FText::FromString(TEXT("Name")));
	const FRoleProperty* BaseProperty = Attribute->GetBaseProperty();
	TB_Type->SetText(UEnum::GetDisplayValueAsText(BaseProperty->Type));
	TB_Level->SetText(FText::FromString(FString::FromInt(BaseProperty->Level)));
	FString EXPText = FString::FromInt(BaseProperty->Exp) + "/" + FString::FromInt(100 * BaseProperty->Level);
	TB_EXP->SetText(FText::FromString(EXPText));
	TB_HP->SetText(FText::FromString(FString::FromInt(BaseProperty->MaxHP)));
	TB_MP->SetText(FText::FromString(FString::FromInt(BaseProperty->MaxMP)));
	TB_Attack->SetText(FText::FromString(FString::FromInt(BaseProperty->Attack)));
	TB_Defense->SetText(FText::FromString(FString::FromInt(BaseProperty->Defense)));

	for (int i = 0; i < HeroIconArr.Num(); i++) {
		TObjectPtr<UUI_HeroIcon> Icon = HeroIconArr[i];
		Icon->SetState(Attribute == Icon->RoleAttribute);
	}
}
