// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/RolePropertyComponent.h"

// Sets default values for this component's properties
URolePropertyComponent::URolePropertyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URolePropertyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void URolePropertyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool URolePropertyComponent::InitProperty(FName RowName)
{
	DT_RoleProperty = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_RoleProperty.DT_RoleProperty'")));
	if (DT_RoleProperty) {
		FString ContextString = "Text";
		RoleProperty = DT_RoleProperty->FindRow<FRoleProperty>(RowName, ContextString);
		if (RoleProperty) {
			return true;
		}
	}
	return false;
}

FRoleProperty* getRandomRoleProperty(ERoleType type)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_RoleProperty.DT_RoleProperty'")));
	if (DataTable) {
		FString ContextString = "Text";
		FName RowName = FName(UEnum::GetDisplayValueAsText(type).ToString());
		FRoleProperty* RoleProperty = DataTable->FindRow<FRoleProperty>(RowName, ContextString);
		if (RoleProperty) {
			FRoleProperty* rp = new FRoleProperty(*RoleProperty);
			return rp;
		}
	}
	return nullptr;
}
