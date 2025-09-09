// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "SAPlayerState.generated.h"

class USAAbilitySystemComponent;
class USAAttributeSet;

UCLASS()
class SPINBOTARENA_API ASAPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASAPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual USAAttributeSet* GetAttributeSet() const;

protected:
	UPROPERTY()
	TObjectPtr<USAAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<USAAttributeSet> AttributeSet;

};
