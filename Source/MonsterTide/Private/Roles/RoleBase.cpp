// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/RoleBase.h"
#include "Roles/RolePropertyComponent.h"
#include "Data/RolePropertyData.h"
#include "Data/SkillData.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ARoleBase::ARoleBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ARoleBase::InitRole(FRoleProperty* RoleProperty)
{
	for (int i = 0; i < RoleProperty->Skill.Num(); i++) {
		RoleSkill.SkillCD.Push(0.f);
		RoleSkill.SkillConfigArray.Push(*GetSkillConfig(RoleProperty->Skill[i]));
	}
	RolePropertyComponent = GetComponentByClass<URolePropertyComponent>();
	if (RolePropertyComponent) {
		RolePropertyComponent->InitProperty(RoleProperty);
	}
}

void ARoleBase::RemoveRole()
{
	Destroy();
}

bool ARoleBase::IsDead()
{
	return RolePropertyComponent->IsDead();
}

void ARoleBase::ChangeHP(float Value)
{
	if (RolePropertyComponent->ChangeHP(Value) == 0) {
		Dead();
	}
}

void ARoleBase::ChangeMP(float Value)
{
	RolePropertyComponent->ChangeMP(Value);
}

float ARoleBase::OnHit(float Damage)
{
	ChangeHP(-Damage);
	return Damage;
}

const FRoleProperty* ARoleBase::GetRoleProperty()
{
	return RolePropertyComponent->GetRoleProperty();
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
	float SphereRadius = RolePropertyComponent->GetRoleProperty()->Range;  // ����뾶

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
		EDrawDebugTrace::None, // ������ʾ��ʽ
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

float ARoleBase::UseSkill()
{
	return  RolePropertyComponent->GetRoleProperty()->SkillInterval;
}

int ARoleBase::GetNextSkill()
{
	int index = -1;
	int i = 0;
	while (i < RoleSkill.SkillCD.Num()) {
		if (RoleSkill.SkillCD[RoleSkill.NextSkill] == 0 &&
			RolePropertyComponent->GetRoleProperty()->MP >= RoleSkill.SkillConfigArray[RoleSkill.NextSkill].Consume) {
			index = RoleSkill.NextSkill;
		}
		RoleSkill.NextSkill = (RoleSkill.NextSkill + 1) % RoleSkill.SkillCD.Num();
		if (index >= 0)
			break;
		i++;
	}
	return index;
}

void ARoleBase::Dead()
{
	RemoveRole();
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
	RolePropertyComponent->RecoveryProperty(DeltaTime);
}
