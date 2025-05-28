// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/EnemyManager.h"
#include "Roles/Enemys/EnemyBase.h"
#include "Roles/RoleAttribute.h"
#include "Data/GameEnemyData.h"
#include "Data/RolePropertyData.h"


FCreateStruct::FCreateStruct(FGameEnemyConfig* Cfg)
{
	GameEnemyConfig = new FGameEnemyConfig(Cfg);
}

void UEnemyManager::CreateEnemys(FGameEnemyConfig EnemyConfig)
{
	CreateEnemy(EnemyConfig);
	if (EnemyConfig.Number > 1) {
		EnemyConfig.Number -= 1;
		FTimerHandle TimerHandle = FTimerHandle();
		// 创建委托并绑定参数
		FTimerDelegate TimerDelegate = FTimerDelegate();
		TimerDelegate.BindUFunction(this, FName("CreateEnemy"), EnemyConfig);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, EnemyConfig.Interval, true);
		FCreateStruct* CreateStruct = new FCreateStruct(&EnemyConfig);
		CreateStruct->TimerHandle = TimerHandle;
		CreateStruct->TimerDelegate = TimerDelegate;
		CreateArray.Push(CreateStruct);
	}
}

int UEnemyManager::GetEnemyNumber() const
{
	int Num = EnemyArray.Num();
	for (FCreateStruct* CreateStruct : CreateArray) {
		Num += CreateStruct->GameEnemyConfig->Number;
	}
	return Num;
}

void UEnemyManager::CreateEnemy(FGameEnemyConfig EnemyConfig)
{
	FEnemyPropertyConfig* EnemyPropertyConfig = GetEnemyPropertyConfig(EnemyConfig.Type);
	TSubclassOf<AEnemyBase> RoleClass = EnemyPropertyConfig->EnemyClass;
	if (RoleClass) {
		FVector SpawnLocation(0, 0, 0); // 生成位置
		FRotator SpawnRotation(0, 0, 0);  // 生成旋转
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AEnemyBase* Enemy = GetWorld()->SpawnActor<AEnemyBase>(RoleClass, SpawnLocation, SpawnRotation, SpawnParams);
		// TODO : 下方初始化的时候传入样条名称
		FRoleProperty* RoleProperty = GetRandomEnemyProperty(EnemyPropertyConfig->Type, EnemyConfig.EnemyLevel);
		URoleAttribute* EnemyAttribute = NewObject<URoleAttribute>();
		EnemyAttribute->SetBaseProperty(*RoleProperty);
		Enemy->InitRole(EnemyAttribute);
		Enemy->InitEnemy(EnemyConfig.Path, EnemyPropertyConfig->Damage);
		Enemy->OnEnemyDead.AddUObject(this, &UEnemyManager::OnEnemyDead);
		Enemy->OnEnemyArrived.AddUObject(this, &UEnemyManager::OnEnemyArrived);
		EnemyArray.Push(Enemy);
	}

	for (FCreateStruct* CreateStruct : CreateArray) {
		if (GameEnemyConfigEqual(CreateStruct->GameEnemyConfig, &EnemyConfig)) {
			CreateStruct->GameEnemyConfig->Number -= 1;
			if (CreateStruct->GameEnemyConfig->Number <= 0) {
				GetWorld()->GetTimerManager().ClearTimer(CreateStruct->TimerHandle);
				CreateArray.Remove(CreateStruct);
			}
			break;
		}
	}
}

void UEnemyManager::RemoveEnemy(TObjectPtr<AEnemyBase> Enemy)
{
	EnemyArray.Remove(Enemy);
}

void UEnemyManager::OnEnemyDead(TObjectPtr<AEnemyBase> Enemy)
{
	RemoveEnemy(Enemy);
	EnemyDead.Broadcast(Enemy);
}

void UEnemyManager::OnEnemyArrived(TObjectPtr<AEnemyBase> Enemy)
{
	RemoveEnemy(Enemy);
	EnemyArrived.Broadcast(Enemy);
}
