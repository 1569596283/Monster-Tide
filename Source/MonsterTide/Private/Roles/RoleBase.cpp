// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/RoleBase.h"
#include "Roles/RolePropertyComponent.h"
#include "Data/RolePropertyData.h"
#include "Data/SkillData.h"
#include <Kismet/KismetSystemLibrary.h>

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

TArray<TObjectPtr<AActor>> ARoleBase::GetTargetWithinRange(ECollisionChannel Channel)
{
	UWorld* World = GetWorld();
	if (!World) return {};

	FVector StartLocation = GetActorLocation(); // �������
	FVector EndLocation = GetActorLocation();   // �����յ�
	float SphereRadius = CurRoleProperty->Range;  // ����뾶

	// ����Ҫ����Object����
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(Channel)); // ��̬����
	// ��Ӹ�������Ҫ������...
	// ���Ե�Actor
	TArray<AActor*> ActorsToIgnore;
	// �洢���н��
	TArray<FHitResult> OutHits;

	// ִ�ж�����׷��
	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		World,
		StartLocation,
		EndLocation,
		SphereRadius,
		ObjectTypes,
		false, // �Ƿ�׷�ٸ�����ײ
		ActorsToIgnore,
		EDrawDebugTrace::ForOneFrame, // ������ʾ��ʽ
		OutHits,
		true // ��������
	);

	TArray<TObjectPtr<AActor>> HitActorArr;
	if (bHit)
	{
		for (const FHitResult& Hit : OutHits)
		{
			UObject* HitObject = Hit.GetActor();
			if (HitObject)
			{
				// �����AActor�����Խ�һ������
				if (TObjectPtr<AActor> HitActor = Cast<AActor>(HitObject))
				{
					HitActorArr.Push(HitActor);
				}
			}
		}
	}
	return HitActorArr;
}

// Called to bind functionality to input
void ARoleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARoleBase::InitRole(FRoleProperty* RoleProperty)
{
	CurRoleProperty = RoleProperty;
	if (RolePropertyComponent) {
		RolePropertyComponent->InitProperty(RoleProperty);
	}
	for (int i = 0; i < RoleProperty->Skill.Num(); i++) {
		RoleSkill.SkillCD.Push(0.f);
		RoleSkill.SkillConfigArray.Push(*GetSkillConfig(RoleProperty->Skill[i]));
	}
}

void ARoleBase::RemoveRole()
{
	Destroy();
}

bool ARoleBase::IsDead()
{
	if (CurRoleProperty) {
		return CurRoleProperty->HP <= 0;
	}
	return true;
}


float ARoleBase::UseSkill()
{
	return CurRoleProperty->SkillInterval;
}

int ARoleBase::GetNextSkill()
{
	int index = -1;
	int i = 0;
	while (i < RoleSkill.SkillCD.Num()) {
		if (RoleSkill.SkillCD[RoleSkill.NextSkill] == 0 &&
			CurRoleProperty->MP >= RoleSkill.SkillConfigArray[RoleSkill.NextSkill].Consume) {
			index = RoleSkill.NextSkill;
		}
		RoleSkill.NextSkill = (RoleSkill.NextSkill + 1) % RoleSkill.SkillCD.Num();
		if (index >= 0)
			break;
		i++;
	}
	return index;
}

void ARoleBase::SkillTiming(float DeltaTime)
{
	if (RoleSkill.SkillCD.Num() == 0) {
		return;
	}
	for (int i = 0; i < RoleSkill.SkillCD.Num(); i++) {
		if (RoleSkill.SkillCD[i] > 0.f) {
			RoleSkill.SkillCD[i] = FMath::Max(0, RoleSkill.SkillCD[i] - DeltaTime);
		}
	}
	RoleSkill.Interval = FMath::Max(0, RoleSkill.Interval - DeltaTime);
	if (RoleSkill.Interval == 0.f) {
		RoleSkill.Interval = UseSkill();
	}
}

// Called every frame
void ARoleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SkillTiming(DeltaTime);
}
