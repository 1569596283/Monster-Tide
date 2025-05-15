// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_RoleProperty.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API UUI_RoleProperty : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetLevel(int Level);
	void SetHP(float Percent);
	void SetMP(float Percent);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_Level;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_HP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_MP;

};
