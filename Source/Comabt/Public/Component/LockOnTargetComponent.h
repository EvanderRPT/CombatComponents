// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnTargetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COMABT_API ULockOnTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULockOnTargetComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LockOnTarget")
	float LockOnRadius = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LockOnTarget")
	float RotationSpeed = 6.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockOnTarget")
	TSubclassOf<AActor> TargetClass;
	
	UFUNCTION(BlueprintCallable, Category="LockOnTarget")
	void ToggleLockOn();

	UFUNCTION(BlueprintCallable, Category="LockOnTarget")
	void ClearTarget();

	

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TObjectPtr<AActor> CurrentTarget;

	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;

	AActor* FindNearestTarget();

	float Distance;
};
