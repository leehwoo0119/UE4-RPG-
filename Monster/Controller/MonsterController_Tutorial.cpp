// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController_Tutorial.h"

AMonsterController_Tutorial::AMonsterController_Tutorial()
{
	aiSightRadius = 1000.0f;
	aiLoseSightRadius = 1700.0f;
	aiFieldOfView = 60.0f;
	aiViewBackwardOffset = 100.0f;
	aiNearClippingRadius = 100.0f;
	aiHearingRange = 1000.0f;

	PerceptionSetting();

	// BT�� BB�� ������ BP���� ����
}

void AMonsterController_Tutorial::BeginPlay()
{
	Super::BeginPlay();

}