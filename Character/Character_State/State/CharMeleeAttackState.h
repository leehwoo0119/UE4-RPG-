// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharState.h"
#include "CharMeleeAttackState.generated.h"

UCLASS()
class LHW_API UCharMeleeAttackState : public UCharState
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UCharMeleeAttackState();

protected:
	// Called when the game starts
	void BeginPlay() override;

public:
	void Enter()override;

	void Execute()override;

	void Exit()override;
};
