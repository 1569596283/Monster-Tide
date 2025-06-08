// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/UI_Hero.h"
#include "UI/Main/UI_HeroIcon.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Game/MainPlayerController.h"
#include "Roles/HeroManager.h"
#include "Roles/RoleAttribute.h"
#include "Data/RolePropertyData.h"
#include "Data/HeroInfoData.h"
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>


void UUI_Hero::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Btn_Return != nullptr) {
		Btn_Return->OnClicked.AddDynamic(this, &UUI_Hero::OnBtnReturnClicked);
	}
	ShowHeros();
	ET_Name->OnTextCommitted.AddDynamic(this, &UUI_Hero::ChangeHeroName);
}

void UUI_Hero::OnBtnReturnClicked()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;
	if (AMainPlayerController* MainPC = Cast<AMainPlayerController>(PC)) {
		MainPC->CloseHeroUMG();
	}
}

void UUI_Hero::ChangeHeroName(const FText& Text, ETextCommit::Type CommitMethod)
{
	auto HeroMgr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>();
	if (HeroMgr->GetHeroInfo(HeroAttribute).Name == Text.ToString()) {
		return;
	}
	FString NewName = HeroMgr->ChangeHeroName(HeroAttribute, Text.ToString());
	ET_Name->SetText(FText::FromString(NewName));
}

void UUI_Hero::ShowHeros()
{
	if (!WB_Heros || !HeroIconClass) {
		return;
	}
	auto HeroMgr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>();
	TArray<TObjectPtr<URoleAttribute>> Heros = HeroMgr->GetAllHeroAttributeArray();
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
	if (HeroAttribute == Attribute) {
		return;
	}
	HeroAttribute = Attribute;
	const FRoleProperty* BaseProperty = Attribute->GetBaseProperty();
	FHeroInfo HeroInfo = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->GetHeroInfo(Attribute);
	ET_Name->SetText(FText::FromString(HeroInfo.Name));
	TB_Type->SetText(UEnum::GetDisplayValueAsText(HeroInfo.Type));
	TB_Level->SetText(FText::FromString(FString::FromInt(HeroInfo.Level)));
	FString EXPText = FString::FromInt(HeroInfo.Exp) + "/" + FString::FromInt(100 * HeroInfo.Level);
	TB_EXP->SetText(FText::FromString(EXPText));
	TB_HP->SetText(FText::FromString(FString::FromInt(BaseProperty->MaxHP)));
	TB_MP->SetText(FText::FromString(FString::FromInt(BaseProperty->MaxMP)));
	TB_Attack->SetText(FText::FromString(FString::FromInt(BaseProperty->Attack)));
	TB_Defense->SetText(FText::FromString(FString::FromInt(BaseProperty->Defense)));

	for (int i = 0; i < HeroIconArr.Num(); i++) {
		TObjectPtr<UUI_HeroIcon> Icon = HeroIconArr[i];
		Icon->SetState(Attribute == Icon->RoleAttribute);
	}
	RefreshHeroModel(HeroInfo.Type);
}

void UUI_Hero::RefreshHeroModel(ERoleType Type)
{
	if (!HeroModel) {
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundActors);
		// 遍历并处理每个Character
		for (AActor* Actor : FoundActors)
		{
			if (Actor->GetActorLabel() == "HeroModel")
			{
				HeroModel = Cast<ACharacter>(Actor);
			}
		}
	}
	USkeletalMeshComponent* MeshComp = HeroModel->GetMesh();
	TObjectPtr<USkeletalMesh> SkeletalMesh = GetHeroSkeletalMesh(Type);
	if (MeshComp && SkeletalMesh)
	{
		MeshComp->SetSkeletalMesh(SkeletalMesh);
	}
}
