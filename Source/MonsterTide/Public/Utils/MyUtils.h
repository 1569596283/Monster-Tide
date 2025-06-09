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
    // 构造函数
    UMyUtils();

    // 静态方法可以直接调用，无需创建实例
    UFUNCTION(BlueprintCallable, Category = "MyUtility|Random", meta = (DisplayName = "Get Random Index By Weight"))
    static int GetRandomIndexByWeight(const TArray<float>& Weights);
};
