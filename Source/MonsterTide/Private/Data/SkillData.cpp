// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/SkillData.h"

FSkillConfig* GetSkillConfig(ESkillType Type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_Skill.DT_Skill'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(UEnum::GetDisplayValueAsText(Type).ToString());
		FSkillConfig* SkillConfig = DataTable->FindRow<FSkillConfig>(RowName, ContextString);
		if (SkillConfig) {
			return SkillConfig;
		}
	}
	return nullptr;
}
