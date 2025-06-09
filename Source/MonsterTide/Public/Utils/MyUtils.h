// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyUtils.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API UMyUtils : public UObject
{
	GENERATED_BODY()

public:
    // ���캯��
    UMyUtils();

    // ��̬��������ֱ�ӵ��ã����贴��ʵ��
    UFUNCTION(BlueprintCallable, Category = "MyUtility|Random", meta = (DisplayName = "Get Random Index By Weight"))
    static int GetRandomIndexByWeight(const TArray<float>& Weights);
};
