// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterNormal_KN_CombatComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MonsterStateMachine.h"
#include "MonsterBase.h"
#include "MonsterBaseStatus.h"
#include "MonsterBaseAnimInstance.h"
#include "MonsterBase_Normal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "LHW/MainChar.h"

// Sets default values for this component's properties
UMonsterNormal_KN_CombatComponent::UMonsterNormal_KN_CombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UMonsterNormal_KN_CombatComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UMonsterNormal_KN_CombatComponent::TakeDamage(AActor* _damagedActor, float _damage, const UDamageType* _damageType, AController* _instigatedBy, AActor* _damageCauser)
{
	Super::TakeDamage(_damagedActor, _damage, _damageType, _instigatedBy, _damageCauser);

	if (monsterBase->MON_BEHAVIORSTATE == EAI_Behavior_State::Die ||
		monsterBase->MON_COMBATSTATE == EAI_Combat_State::OffenserseZero) return;

	AMainChar* checkMainChar = Cast<AMainChar>(_damageCauser);
	if (checkMainChar)
	{
		ExecuteTakeDamageOffenserse(-_damage);
	}

	FRotator findLookAtRot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), _damageCauser->GetActorLocation());
	float hitDirection =
		UKismetMathLibrary::NormalizedDeltaRotator(
			GetOwner()->GetActorRotation(), findLookAtRot).Yaw;

	ExecuteTakeDamageHealth(_damage);

	if (monsterBase->MON_COMBATSTATE == EAI_Combat_State::SpecialSkill)return;
	TakeDamageCheckDir(hitDirection);	
}

void UMonsterNormal_KN_CombatComponent::Attack(EAI_MeleeAttack_State _state)
{
	Super::Attack(_state);

	monsterBase->bUseControllerRotationYaw = true;
	switch (_state)
	{
	case EAI_MeleeAttack_State::AttackGroup_1:
		MeleeAttackGroup_1();
		break;
	case EAI_MeleeAttack_State::AttackGroup_2:
		MeleeAttackGroup_2();
		break;
	default:
		break;
	}
}

void UMonsterNormal_KN_CombatComponent::MeleeAttackGroup_1()
{
	Super::MeleeAttackGroup_1();

	monsterBase->MON_STATEMACHINE->SetMeleeAttackState(EAI_MeleeAttack_State::AttackGroup_2);
	monsterBase->MON_STATEMACHINE->SetAttackTypeState(EAI_AttackType_State::NormalTypeAttack);

	switch (FMath::RandRange(0, maxMeleeAttackValue))
	{
	case 0:
		monsterBase->MON_ANIM->AnimMontagePlay(monsterBase->MON_ANIM->attackMontage, 0.9f, FName("Attack_1"));
		break;
	case 1:
		monsterBase->MON_ANIM->AnimMontagePlay(monsterBase->MON_ANIM->attackMontage, 0.9f, FName("Attack_2"));
		break;
	case 2:
		monsterBase->MON_ANIM->AnimMontagePlay(monsterBase->MON_ANIM->attackMontage, 0.9f, FName("Attack_3"));
		break;
	default:
		break;
	}
}

void UMonsterNormal_KN_CombatComponent::MeleeAttackGroup_2()
{
	Super::MeleeAttackGroup_2();

	monsterBase->MON_STATEMACHINE->SetMeleeAttackState(EAI_MeleeAttack_State::AttackGroup_1);
	monsterBase->MON_STATEMACHINE->SetAttackTypeState(EAI_AttackType_State::NormalTypeAttack);

	monsterBase->MON_ANIM->AnimMontagePlay(monsterBase->MON_ANIM->attackMontage, 0.9f, FName("Attack_4"));
}

void UMonsterNormal_KN_CombatComponent::AttackBlock()
{
	Super::AttackBlock();
	
	monsterBase->MON_STATUS->SetDefenseCnt(0);
	ExecuteTakeDamageOffenserse(monsterBase->GetMonsterStatus()->GetMaxMonsterOffensersePoint() * -0.1f);
	monsterBase->MON_ANIM->AnimMontagePlay(monsterBase->MON_ANIM->attackMontage, 1.0f, FName("AttackBlock"));
}

void UMonsterNormal_KN_CombatComponent::SpecialSkill()
{
	Super::SpecialSkill();

	monsterBase->bUseControllerRotationYaw = true;
	monsterBase->MON_STATUS->SetCantParryingAttack(true);
	monsterBase->MON_STATEMACHINE->SetCombatState(EAI_Combat_State::SpecialSkill);
	monsterBase->MON_STATEMACHINE->SetAttackTypeState(EAI_AttackType_State::SpecialTypeAttack);

	monsterBase->MON_ANIM->AnimMontagePlay(monsterBase->MON_ANIM->specialSkillMontage, 1.2f, FName("SpecialAttack"));
}

void UMonsterNormal_KN_CombatComponent::LookAround(bool _stop)
{
	if (_stop)
		monsterBase->StopAnimMontage(monsterBase->MON_ANIM->lookAroundMontage);
	else
		monsterBase->MON_ANIM->AnimMontagePlay(monsterBase->MON_ANIM->lookAroundMontage, 1.0f, FName("LookAround"));
}




