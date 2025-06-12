// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/SkillData.h"
#include "Data/DataTableSettings.h"

FSkillConfig* GetSkillConfig(ESkillType Type)
{
	UDataTable* DataTable = GetMutableDefault<UDataTableSettings>()->GetSkillDataTable();
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
