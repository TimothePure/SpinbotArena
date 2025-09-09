// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/GAS/Abilities/SADashAbility.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "Classes/GAS/SAAttributeSet.h"

USADashAbility::USADashAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Event.Dash")));
	
	MaxDashStrength = 2000.f;
	DashingTag = FGameplayTag::RequestGameplayTag(TEXT("State.Dashing"));
}

void USADashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	const USAAttributeSet* AttributeSet = ActorInfo->AbilitySystemComponent->GetSet<USAAttributeSet>();
	float ChargeDuration = AttributeSet ? AttributeSet->GetDashChargeDuration() : 0.f;

	float Normalized = FMath::Clamp(ChargeDuration / 5, 0.f, 1.f);
	float DashStrength = FMath::Lerp(600.f, MaxDashStrength, Normalized);

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (Character)
	{
		FVector Direction = Character->GetActorForwardVector();
		Character->LaunchCharacter(Direction * DashStrength, true, true);

		ActorInfo->AbilitySystemComponent->AddLooseGameplayTag(DashingTag);
	}

	// Set timer to remove dash tag and end ability
	FTimerHandle TimerHandle;
	float DashTime = 0.4f; // however long dash lasts

	FTimerDelegate TimerDel;
	TimerDel.BindLambda([this, Handle, ActorInfo, ActivationInfo]()
	{
		ActorInfo->AbilitySystemComponent->RemoveLooseGameplayTag(DashingTag);
		const_cast<USADashAbility*>(this)->EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	});

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, DashTime, false);
}

void USADashAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ActorInfo->AbilitySystemComponent->RemoveLooseGameplayTag(DashingTag);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
