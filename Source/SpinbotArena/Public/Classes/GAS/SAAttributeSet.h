// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "SAAbilitySystemComponent.h"
#include "SAAttributeSet.generated.h"

// Macro to declare attributes
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \
	
UCLASS()
class SPINBOTARENA_API USAAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// Constructor
	USAAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	/** Percentage Attribute **/ 
	UPROPERTY(BlueprintReadOnly, Category = "Percentage", ReplicatedUsing = OnRep_Percentage)
	FGameplayAttributeData Percentage;
	ATTRIBUTE_ACCESSORS(USAAttributeSet, Percentage)

	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_Speed)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(USAAttributeSet, Speed)

	UPROPERTY(BlueprintReadOnly, Category = "Ground Friction", ReplicatedUsing = OnRep_GroundFriction)
	FGameplayAttributeData GroundFriction;
	ATTRIBUTE_ACCESSORS(USAAttributeSet, GroundFriction)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash", ReplicatedUsing = OnRep_ChargeDuration)
	FGameplayAttributeData DashChargeDuration;
	ATTRIBUTE_ACCESSORS(USAAttributeSet, DashChargeDuration)

protected:
	/** Replication Notifies **/
	UFUNCTION()
	virtual void OnRep_Percentage(const FGameplayAttributeData& OldPercentage);

	UFUNCTION()
	virtual void OnRep_Speed(const FGameplayAttributeData& OldSpeed);

	UFUNCTION()
	virtual void OnRep_GroundFriction(const FGameplayAttributeData& OldGroundFriction);

	UFUNCTION()
	virtual void OnRep_ChargeDuration(const FGameplayAttributeData& OldChargeDuration);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

};
