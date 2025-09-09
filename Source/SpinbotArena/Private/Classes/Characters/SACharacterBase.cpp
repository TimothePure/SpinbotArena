// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/Characters/SACharacterBase.h"
#include "Classes/GAS/SAAbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


#include "Net/UnrealNetwork.h"


// Sets default values
ASACharacterBase::ASACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

USAAbilitySystemComponent* ASACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

USAAttributeSet* ASACharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ASACharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASACharacterBase, AbilitySystemComponent);
	DOREPLIFETIME(ASACharacterBase, AttributeSet);
}

void ASACharacterBase::GiveDefaultAbilities()
{
	check(AbilitySystemComponent);
	if (!HasAuthority()) return;

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void ASACharacterBase::InitDefaultAttributes() const
{
	if (!AbilitySystemComponent || !DefaultAttributeEffect) return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1.f, EffectContext);

	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
} 
