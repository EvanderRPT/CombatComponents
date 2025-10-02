// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, NewStamina);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COMABT_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStaminaComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category="Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, Category="Stamina")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, Category="Stamina")
	float StaminaRegenRate = 20.f;

	UPROPERTY(BlueprintAssignable, Category="Stamina")
	FOnStaminaChanged OnStaminaChanged;

	FTimerHandle OnStaminaTimerHandle;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Stamina")
	bool ConsumeStamina(float Amount);

	UFUNCTION(BlueprintCallable, Category="Stamina")
	void StartRegeneration();

	UFUNCTION(BlueprintCallable, Category="Stamina")
	void StopReGeneration();

	UFUNCTION(BlueprintCallable, Category="Stamina")
	float GetStaminaPercent() const { return  CurrentStamina / MaxStamina; }

	
};
