// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/SkillBase.h"
#include "Data/SkillData.h"
#include "Data/RolePropertyData.h"
#include "Roles/RoleBase.h"

// Sets default values
ASkillBase::ASkillBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkillBase::InitSkill(ESkillType Type, TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target)
{
	SkillConfig = GetSkillConfig(Type);
	TargetRole = Target;
	TargetLocation = Target->GetActorLocation();
	UserRole = User;
	Damage = UserRole->GetRoleProperty()->Attack * SkillConfig->Multiple;
}

// Called when the game starts or when spawned
void ASkillBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASkillBase::Move(float DeltaTime)
{
	if (IsValid(TargetRole)) {
		TargetLocation = TargetRole->GetActorLocation();
	}
	FVector CurLocation = this->GetActorLocation();
	float Distance = DeltaTime * SkillConfig->Speed;
	if (FVector::PointsAreNear(TargetLocation, CurLocation, Distance)) {
		if (IsValid(TargetRole)) {
			float damage = TargetRole->OnHit(Damage, UserRole);
		}
		Destroy();
		return;
	}
	FVector Direction = TargetLocation - CurLocation;
	Direction.Normalize();
	CurLocation = CurLocation + (Distance * Direction);

	SetActorLocation(CurLocation);
}

// Called every frame
void ASkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

