// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/Characters/SAPlayerCharacter.h"
#include "Classes/GAS/SAAbilitySystemComponent.h"
#include "Classes/Player/SAPlayerState.h"
#include "Classes/GAS/SAAttributeSet.h"

// Sets default values
ASAPlayerCharacter::ASAPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Server side
void ASAPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponent();
	GiveDefaultAbilities();
	InitDefaultAttributes();
}

// Client side
void ASAPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitySystemComponent();
	InitDefaultAttributes();
}

void ASAPlayerCharacter::InitAbilitySystemComponent()
{
	ASAPlayerState* SAPlayerState = GetPlayerState<ASAPlayerState>();
	check(SAPlayerState);
	AbilitySystemComponent = CastChecked<USAAbilitySystemComponent>(SAPlayerState->GetAbilitySystemComponent());
	AbilitySystemComponent->InitAbilityActorInfo(SAPlayerState, this);
	AttributeSet = SAPlayerState->GetAttributeSet();
}
