// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Hero.generated.h"

enum class ERoleType : uint8;
class UButton;
class UTextBlock;
class UImage;
class UWrapBox;
class UUI_HeroIcon;
class URoleAttribute;

/**
 *
 */
UCLASS()
class MONSTERTIDE_API UUI_Hero : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Return;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Name;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Type;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Level;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_EXP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_HP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_MP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Attack;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Defense;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> Img_Hero;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UWrapBox> WB_Heros;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_HeroIcon> HeroIconClass;
	UPROPERTY(BlueprintReadOnly)
	TArray <TObjectPtr< UUI_HeroIcon >> HeroIconArr;

	UFUNCTION()
	void OnBtnReturnClicked();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACharacter> HeroModel;

private:
	void ShowHeros();

	void RefreshHeroInfo(TObjectPtr<URoleAttribute> Attribute);

	void RefreshHeroModel(ERoleType Type);
};
