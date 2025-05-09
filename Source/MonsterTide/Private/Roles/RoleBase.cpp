// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/RoleBase.h"
#include "Roles/RolePropertyComponent.h"

// Sets default values
ARoleBase::ARoleBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RolePropertyComponent = CreateDefaultSubobject<URolePropertyComponent>(TEXT("RoleProperty"));
}

// Called when the game starts or when spawned
void ARoleBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARoleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARoleBase::InitRole(FRoleProperty* RoleProperty)
{
	if (RolePropertyComponent) {
		RolePropertyComponent->InitProperty(RoleProperty);
	}
}

