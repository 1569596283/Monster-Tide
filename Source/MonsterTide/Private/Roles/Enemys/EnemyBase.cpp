// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/Enemys/EnemyBase.h"
#include "Roles/RoleAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"
#include "Components/CapsuleComponent.h"
#include "Levels/Spline.h"

AEnemyBase::AEnemyBase()
{
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	if (Capsule)
	{
		Capsule->SetCollisionProfileName(TEXT("Enemy"));
	}
}

void AEnemyBase::InitEnemy(int Path,int Damage,float Exp)
{
	CurDamage = Damage;
	Distance = 0.f;
	EnemyExp = Exp;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpline::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		if (ASpline* DerivedActor = Cast<ASpline>(Actor))
		{
			if (DerivedActor->GetPath() == Path) {
				SplineComponent = DerivedActor->SplineComponent;
			}
		}
	}
}

int AEnemyBase::GetDamage() const
{
	return CurDamage;
}

int AEnemyBase::GetEnemyExp() const
{
	return EnemyExp;
}

float AEnemyBase::GetRemainDistance() const
{
	return SplineComponent->GetSplineLength() - Distance;
}

void AEnemyBase::RemoveRole()
{
	Super::RemoveRole();
}

void AEnemyBase::Move(float DeltaTime)
{
	Distance += DeltaTime * 100;
	FVector LocationAtDistance = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FRotator RotationAtDistance = SplineComponent->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	LocationAtDistance.Z = GetActorLocation().Z;
	SetActorLocation(LocationAtDistance);
	SetActorRotation(RotationAtDistance);
	if (Distance > SplineComponent->GetSplineLength()) {
		OnEnemyArrived.Broadcast(this);
		RemoveRole();
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void AEnemyBase::Dead()
{
	Super::Dead();
	OnEnemyDead.Broadcast(this);
}
