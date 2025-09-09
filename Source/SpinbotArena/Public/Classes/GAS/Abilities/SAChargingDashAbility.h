// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SAChargingDashAbility.generated.h"

/**
 * 
 */
UCLASS()
class SPINBOTARENA_API USAChargingDashAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	USAChargingDashAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							   const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	float ChargeStartTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float MinChargeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float MaxChargeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	FGameplayTag ChargingTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	FGameplayTag DashEventTag;
};
