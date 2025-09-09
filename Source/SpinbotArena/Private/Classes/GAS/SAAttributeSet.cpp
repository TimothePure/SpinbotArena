// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/GAS/SAAttributeSet.h"
#include "Net/UnrealNetwork.h"

USAAttributeSet::USAAttributeSet()
{
	Percentage.SetBaseValue(0.f);
	Percentage.SetCurrentValue(0.f);
	Speed.SetBaseValue(300.f);
	Speed.SetCurrentValue(300.f);
	GroundFriction.SetBaseValue(8.f);
	GroundFriction.SetCurrentValue(8.f);
}

void USAAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USAAttributeSet, Percentage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USAAttributeSet, Speed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USAAttributeSet, GroundFriction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USAAttributeSet, DashChargeDuration, COND_None, REPNOTIFY_Always);
}

void USAAttributeSet::OnRep_Percentage(const FGameplayAttributeData& OldPercentage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USAAttributeSet, Percentage, OldPercentage);
}

void USAAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USAAttributeSet, Speed, OldSpeed);
}

void USAAttributeSet::OnRep_GroundFriction(const FGameplayAttributeData& OldGroundFriction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USAAttributeSet, GroundFriction, OldGroundFriction);
}

void USAAttributeSet::OnRep_ChargeDuration(const FGameplayAttributeData& OldChargeDuration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USAAttributeSet, DashChargeDuration, OldChargeDuration);
}

void USAAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void USAAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

