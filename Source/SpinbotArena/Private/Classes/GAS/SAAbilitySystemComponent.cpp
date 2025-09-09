// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/GAS/SAAbilitySystemComponent.h"

USAAbilitySystemComponent::USAAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}
