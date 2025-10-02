// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StaminaComponent.h"


UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentStamina = MaxStamina;
}


void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UStaminaComponent::ConsumeStamina(float Amount)
{
	if (CurrentStamina < Amount)
	{
		return false;
	}

	CurrentStamina -= Amount;

	OnStaminaChanged.Broadcast(CurrentStamina);

	StopReGeneration();
	GetWorld()->GetTimerManager().SetTimer(OnStaminaTimerHandle, this, &UStaminaComponent::StartRegeneration, 1.5f, false);
	return true;
}

void UStaminaComponent::StartRegeneration()
{
	GetWorld()->GetTimerManager().SetTimer(OnStaminaTimerHandle, [this]()
	{
		CurrentStamina = FMath::Min(CurrentStamina + StaminaRegenRate * GetWorld()->GetDeltaSeconds(), MaxStamina);

		OnStaminaChanged.Broadcast(CurrentStamina);
		if (CurrentStamina >= MaxStamina)
		{
			StopReGeneration();
		}
		
	}, 0.1f, true);
}

void UStaminaComponent::StopReGeneration()
{
	GetWorld()->GetTimerManager().ClearTimer(OnStaminaTimerHandle);
}

