// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/SkillBase.h"
#include "Data/SkillData.h"
#include "Data/RolePropertyData.h"
#include "Roles/RoleBase.h"
#include "Roles/Enemys/EnemyBase.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
ASkillBase::ASkillBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkillBase::InitSkill(ESkillType Type, float Damage, TObjectPtr<ARoleBase> User, TObjectPtr<ARoleBase> Target)
{
	SkillConfig = GetSkillConfig(Type);
	TargetRole = Target;
	TargetLocation = Target->GetActorLocation();
	UserRole = User;
	SkillDamage = Damage;
	CollisionChannel = Cast<AEnemyBase>(Target) ? ECC_GameTraceChannel2 : ECC_GameTraceChannel1;
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
		Arrive();
	}
	FVector Direction = TargetLocation - CurLocation;
	Direction.Normalize();
	CurLocation = CurLocation + (Distance * Direction);

	SetActorLocation(CurLocation);
}

void ASkillBase::Arrive()
{
	if (SkillConfig->Range == 0) {
		if (IsValid(TargetRole)) {
			float damage = TargetRole->OnHit(SkillDamage, UserRole);
		}
	}
	else {
		UWorld* World = GetWorld();
		FVector StartLocation = GetActorLocation(); // 设置起点
		FVector EndLocation = GetActorLocation();   // 设置终点

		// 设置要检测的Object类型
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(CollisionChannel)); // 静态物体
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
			SkillConfig->Range,
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
					if (TObjectPtr<ARoleBase> HitActor = Cast<ARoleBase>(HitObject))
					{
						HitActor->OnHit(SkillDamage, UserRole);
					}
				}
			}
		}
	}
	Destroy();
	return;
}

// Called every frame
void ASkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

