// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/MyUtils.h"

UMyUtils::UMyUtils()
{
}

int UMyUtils::GetRandomIndexByWeight(const TArray<float>& Weights)
{
    if (Weights.Num() == 0)
    {
        return -1;
    }

    // 计算权重总和
    float TotalWeight = 0.0f;
    for (float Weight : Weights)
    {
        TotalWeight += Weight;
    }

    // 如果权重总和为0，随机返回一个索引或处理错误情况
    if (TotalWeight <= 0.0f)
    {
        // 可以选择返回-1表示错误，或者均匀随机返回一个索引
        return FMath::RandRange(0, Weights.Num() - 1);
    }

    // 生成一个0到总权重之间的随机数
    float RandomWeight = FMath::FRandRange(0.0f, TotalWeight);
    float WeightSum = 0.0f;

    // 遍历权重数组，找到随机数落入的区间
    for (int i = 0; i < Weights.Num(); ++i)
    {
        WeightSum += Weights[i];
        if (RandomWeight <= WeightSum)
        {
            return i;
        }
    }

    // 理论上不应该执行到这里，但为了安全返回最后一个索引
    return Weights.Num() - 1;
}
