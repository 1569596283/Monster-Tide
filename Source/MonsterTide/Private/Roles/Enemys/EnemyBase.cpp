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

void AEnemyBase::InitEnemy(int Path,int Damage)
{
	CurDamage = Damage;
	Distance = 0.f;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpline::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		if (ASpline* DerivedActor = Cast<ASpline>(Actor))
		{
			if (*DerivedActor->GetActorLabel() == FString::FromInt(Path)) {
				SplineComponent = DerivedActor->SplineComponent;
			}
		}
	}
}

int AEnemyBase::GetDamage() const
{
	return CurDamage;
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
