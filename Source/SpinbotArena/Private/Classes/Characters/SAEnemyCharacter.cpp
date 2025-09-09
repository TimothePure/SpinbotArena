// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/Characters/SAEnemyCharacter.h"
#include "Classes/GAS/SAAbilitySystemComponent.h"


// Sets default values
ASAEnemyCharacter::ASAEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<USAAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<USAAttributeSet>(TEXT("AttributeSet"));
}

void ASAEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	GiveDefaultAbilities();
	InitDefaultAttributes();
}

