// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SACharacterBase.h"
#include "SAEnemyCharacter.generated.h"

UCLASS()
class SPINBOTARENA_API ASAEnemyCharacter : public ASACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAEnemyCharacter();

protected:
	virtual void BeginPlay() override;
};
