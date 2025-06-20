// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/RoleBase.h"
#include "Roles/RolePropertyComponent.h"
#include "Roles/RoleAttribute.h"
#include "Roles/RoleAnimInstance.h"
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

void ARoleBase::InitRole(int Level, TObjectPtr<URoleAttribute> RA)
{
	RoleAttribute = RA;
	const FRoleProperty* RoleProperty = RA->GetRoleProperty();
	for (int i = 0; i < RA->GetRoleProperty()->Skill.Num(); i++) {
		RoleSkill.SkillCD.Push(0.f);
		RoleSkill.SkillConfigArray.Push(*GetSkillConfig(RoleProperty->Skill[i]));
	}
	RolePropertyComponent = GetComponentByClass<URolePropertyComponent>();
	if (RolePropertyComponent) {
		RolePropertyComponent->InitProperty(Level, RA);
	}
	RoleAnimInstance->Speed = RoleProperty->Speed;
}

void ARoleBase::RemoveRole()
{
	Destroy();
}

bool ARoleBase::IsDead()
{
	if (RoleAttribute == nullptr) {
		return true;
	}
	return RoleAttribute->IsDead();
}

float ARoleBase::OnHit(float Damage, TObjectPtr<ARoleBase> Source)
{
	Damage = Damage - GetRoleProperty()->Defense;
	Damage = FMath::Max(Damage * 0.01f, Damage);
	RoleAttribute->ChangeHP(-Damage);
	if (IsDead()) {
		Killer = Source;
		Dead();
	}
	return Damage;
}

const FRoleProperty* ARoleBase::GetRoleProperty()
{
	return RoleAttribute->GetRoleProperty();
}

// Called when the game starts or when spawned
void ARoleBase::BeginPlay()
{
	Super::BeginPlay();
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	UAnimInstance* AnimInstance = SkeletalMesh->GetAnimInstance();
	RoleAnimInstance = Cast<URoleAnimInstance>(AnimInstance);
}

TArray<TObjectPtr<AActor>> ARoleBase::GetTargetWithinRange(ECollisionChannel Channel)
{
	UWorld* World = GetWorld();
	if (!World) return {};

	FVector StartLocation = GetActorLocation(); // 设置起点
	FVector EndLocation = GetActorLocation();   // 设置终点
	float SphereRadius = RoleAttribute->GetRoleProperty()->Range;  // 球体半径

	// 设置要检测的Object类型
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(Channel)); // 静态物体
	// 添加更多你需要的类型...
	// 忽略的Actor
	TArray<AActor*> ActorsToIgnore;
	// 存储命中结果
	TArray<FHitResult> OutHits;

	// 执行多球体追踪
	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		World,
		StartLocation,
		EndLocation,
		SphereRadius,
		ObjectTypes,
		false, // 是否追踪复杂碰撞
		ActorsToIgnore,
		EDrawDebugTrace::None, // 调试显示方式
		OutHits,
		true // 忽略自身
	);

	TArray<TObjectPtr<AActor>> HitActorArr;
	if (bHit)
	{
		for (const FHitResult& Hit : OutHits)
		{
			UObject* HitObject = Hit.GetActor();
			if (HitObject)
			{
				// 如果是AActor，可以进一步处理
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
	return  RoleAttribute->GetRoleProperty()->SkillInterval;
}

int ARoleBase::GetNextSkill()
{
	int index = -1;
	int i = 0;
	while (i < RoleSkill.SkillCD.Num()) {
		if (RoleSkill.SkillCD[RoleSkill.NextSkill] == 0 &&
			RoleAttribute->GetRoleProperty()->MP >= RoleSkill.SkillConfigArray[RoleSkill.NextSkill].Consume) {
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
	PrimaryActorTick.SetTickFunctionEnable(false);
	float Time = RoleAnimInstance->PlayDeadAnimation();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		[this]()
		{
			RemoveRole();
		},
		Time,
		false
	);
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
