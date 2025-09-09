// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SACharacterBase.h"
#include "SAPlayerCharacter.generated.h"

UCLASS()
class SPINBOTARENA_API ASAPlayerCharacter : public ASACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAPlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	void InitAbilitySystemComponent();
	
};
