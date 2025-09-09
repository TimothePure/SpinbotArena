// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/GAS/Abilities/SAChargingDashAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Classes/GAS/Abilities/SADashAbility.h"
#include "Classes/GAS/Effects/SAChargeDurationEffect.h"
#include "GameFramework/Actor.h"

USAChargingDashAbility::USAChargingDashAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	bReplicateInputDirectly = true;

	ChargingTag = FGameplayTag::RequestGameplayTag(TEXT("State.Charging"));
	DashEventTag = FGameplayTag::RequestGameplayTag(TEXT("Event.Dash"));
}

void USAChargingDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ChargeStartTime = GetWorld()->GetTimeSeconds();
	ActorInfo->AbilitySystemComponent->AddLooseGameplayTag(ChargingTag);
}

void USAChargingDashAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	const float ChargeDuration = GetWorld()->GetTimeSeconds() - ChargeStartTime;

	ActorInfo->AbilitySystemComponent->RemoveLooseGameplayTag(ChargingTag);

	if (ChargeDuration < MinChargeTime)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	float ClampedCharge = FMath::Clamp(ChargeDuration, MinChargeTime, MaxChargeTime);

	FGameplayEffectSpecHandle SpecHandle = ActorInfo->AbilitySystemComponent->MakeOutgoingSpec(
		USAChargeDurationEffect::StaticClass(),
		1.0f,
		ActorInfo->AbilitySystemComponent->MakeEffectContext());

	if (SpecHandle.IsValid())
	{
		// Set the SetByCaller magnitude with the charge duration value
		SpecHandle.Data->SetSetByCallerMagnitude(
			FGameplayTag::RequestGameplayTag(TEXT("Data.DashChargeDuration")),
			ClampedCharge);

		// Apply the gameplay effect to self (the ASC owner)
		ActorInfo->AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
	
	ActorInfo->AbilitySystemComponent->TryActivateAbilityByClass(USADashAbility::StaticClass());

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void USAChargingDashAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
