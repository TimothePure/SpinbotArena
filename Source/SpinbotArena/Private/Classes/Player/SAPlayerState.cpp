// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/Player/SAPlayerState.h"
#include "Classes/GAS/SAAbilitySystemComponent.h"
#include "Classes/GAS/SAAttributeSet.h"

ASAPlayerState::ASAPlayerState()
{
	SetNetUpdateFrequency(100.f);
	
	AbilitySystemComponent = CreateDefaultSubobject<USAAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<USAAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ASAPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

USAAttributeSet* ASAPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
