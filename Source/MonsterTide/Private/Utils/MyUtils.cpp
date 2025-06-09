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

    // ����Ȩ���ܺ�
    float TotalWeight = 0.0f;
    for (float Weight : Weights)
    {
        TotalWeight += Weight;
    }

    // ���Ȩ���ܺ�Ϊ0���������һ����������������
    if (TotalWeight <= 0.0f)
    {
        // ����ѡ�񷵻�-1��ʾ���󣬻��߾����������һ������
        return FMath::RandRange(0, Weights.Num() - 1);
    }

    // ����һ��0����Ȩ��֮��������
    float RandomWeight = FMath::FRandRange(0.0f, TotalWeight);
    float WeightSum = 0.0f;

    // ����Ȩ�����飬�ҵ���������������
    for (int i = 0; i < Weights.Num(); ++i)
    {
        WeightSum += Weights[i];
        if (RandomWeight <= WeightSum)
        {
            return i;
        }
    }

    // �����ϲ�Ӧ��ִ�е������Ϊ�˰�ȫ�������һ������
    return Weights.Num() - 1;
}
