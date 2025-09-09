// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/GAS/Effects/SAChargeDurationEffect.h"

#include "Classes/GAS/SAAttributeSet.h"

USAChargeDurationEffect::USAChargeDurationEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo Mod;
	Mod.Attribute = USAAttributeSet::GetDashChargeDurationAttribute();
	Mod.ModifierOp = EGameplayModOp::Override;
	Mod.ModifierMagnitude = FScalableFloat(0.f); // overridden at runtime via SetByCaller

	Mod.SourceTags.RequireTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Data.ChargeDuration")));

	Modifiers.Add(Mod);
}
