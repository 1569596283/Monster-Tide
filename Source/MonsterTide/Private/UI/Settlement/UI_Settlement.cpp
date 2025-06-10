// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Settlement/UI_Settlement.h"
#include "Levels/LevelManager.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

void UUI_Settlement::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Btn_Next != nullptr) {
		Btn_Next->OnClicked.AddDynamic(this, &UUI_Settlement::OnBtnNextClicked);
	}
	if (Btn_Restart != nullptr) {
		Btn_Restart->OnClicked.AddDynamic(this, &UUI_Settlement::OnBtnRestartClicked);
	}
	if (Btn_Return != nullptr) {
		Btn_Return->OnClicked.AddDynamic(this, &UUI_Settlement::OnBtnReturnClicked);
	}
}

void UUI_Settlement::InitResult(bool Victory)
{
	CP_TittleVictory->SetVisibility(Victory ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	CP_TittleDefeat->SetVisibility(Victory ? ESlateVisibility::Collapsed : ESlateVisibility::HitTestInvisible);
	auto LevelMgr = GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>();
	TB_FairyStone->SetText(FText::FromString(FString::FromInt(LevelMgr->GetFairyStone())));
	// 需要补充是否存在下一关的情况
	if (Victory && LevelMgr->HasNextLevel()) {
		SB_Next->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else {
		SB_Next->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUI_Settlement::OnBtnNextClicked()
{
	GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>()->OpenNextLevel();
}

void UUI_Settlement::OnBtnRestartClicked()
{
	GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>()->OpenLevel();
}

void UUI_Settlement::OnBtnReturnClicked()
{
	UGameplayStatics::OpenLevel(this, FName("MainMap"));

}
