// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Classes/GAS/SAAttributeSet.h"
#include "SACharacterBase.generated.h"

class UInputAction;
class UGameplayAbility;
class USAAbilitySystemComponent;
class USAAttributeSet;
class UGameplayEffect;

// UENUM(BlueprintType)
// enum class EGASAbilityInputID : uint8
// {
// 	None UMETA(DisplayName = "None"),
// 	Confirm UMETA(DisplayName = "Confirm"),
// 	Cancel UMETA(DisplayName = "Cancel"),
// };

UCLASS()
class SPINBOTARENA_API ASACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASACharacterBase();

	virtual USAAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual USAAttributeSet* GetAttributeSet() const;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	void GiveDefaultAbilities();
	void InitDefaultAttributes() const; 
	
	UPROPERTY()
	TObjectPtr<USAAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<USAAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;
};
