// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterOffenserseBar.h"
#include "MonsterBase.h"


void UMonsterOffenserseBar::SetMonsterBase(AMonsterBase* _monsterBase)
{
	monsterBase = _monsterBase;
	check(monsterBase != nullptr);
}