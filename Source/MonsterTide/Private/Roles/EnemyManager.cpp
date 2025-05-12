// Fill out your copyright notice in the Description page of Project Settings.


#include "Roles/EnemyManager.h"
#include "Roles/Enemys/EnemyBase.h"
#include "Data/GameEnemyData.h"
#include "Data/RolePropertyData.h"


FCreateStruct::FCreateStruct(FGameEnemyConfig* Cfg)
{
	GameEnemyConfig = new FGameEnemyConfig(Cfg);
}


void UEnemyManager::CreateEnemys(FGameEnemyConfig EnemyConfig)
{
	UE_LOG(LogTemp, Warning, TEXT("CreateEnemys"));
	CreateEnemy(EnemyConfig);
	if (EnemyConfig.Number > 1) {
		EnemyConfig.Number -= 1;
		FTimerHandle TimerHandle = FTimerHandle();
		// ����ί�в��󶨲���
		FTimerDelegate TimerDelegate = FTimerDelegate();
		TimerDelegate.BindUFunction(this, FName("CreateEnemy"), EnemyConfig);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, EnemyConfig.Interval, true);
		FCreateStruct* CreateStruct = new FCreateStruct(&EnemyConfig);
		CreateStruct->TimerHandle = TimerHandle;
		CreateStruct->TimerDelegate = TimerDelegate;
		CreateArray.Push(CreateStruct);
	}
}

void UEnemyManager::CreateEnemy(FGameEnemyConfig EnemyConfig)
{
	UE_LOG(LogTemp, Warning, TEXT("CreateEnemy"));
	TSubclassOf<AEnemyBase> RoleClass = GetEnemySubclass(EnemyConfig.Type);
	if (RoleClass) {
		FVector SpawnLocation(0, 0, 0); // ����λ��
		FRotator SpawnRotation(0, 0, 0);  // ������ת
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AEnemyBase* Enemy = GetWorld()->SpawnActor<AEnemyBase>(RoleClass, SpawnLocation, SpawnRotation, SpawnParams);
		// TODO : �·���ʼ����ʱ������������
		Enemy->InitRole(nullptr);
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
