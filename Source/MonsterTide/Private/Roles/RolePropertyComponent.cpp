// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/RolePropertyComponent.h"
#include "Data/RolePropertyData.h"

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

bool URolePropertyComponent::InitProperty(FRoleProperty* rp)
{
	RoleProperty = rp;
	return true;
}
