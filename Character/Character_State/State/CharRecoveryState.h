// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharState.h"
#include "CharRecoveryState.generated.h"


UCLASS()
class LHW_API UCharRecoveryState : public UCharState
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharRecoveryState();

protected:
	// Called when the game starts
	void BeginPlay() override;

protected:
	void Enter()override;

	void Execute()override;

	void Exit()override;
};
