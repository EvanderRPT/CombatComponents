// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Component/LockOnTargetComponent.h"

#include "Engine/OverlapResult.h"
#include "GameFramework/Character.h"


ULockOnTargetComponent::ULockOnTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void ULockOnTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter> (GetOwner());
	Distance = LockOnRadius * LockOnRadius;
	
}


void ULockOnTargetComponent::ToggleLockOn()
{
	if (CurrentTarget)
	{
		ClearTarget();
	}
	else
	{
		CurrentTarget = FindNearestTarget();
	}
}

AActor* ULockOnTargetComponent::FindNearestTarget()
{
	AActor* TargetActor = nullptr;

	TArray<FOverlapResult> OverlapResult;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(LockOnRadius);
	GetWorld()->OverlapMultiByChannel(OverlapResult, OwnerCharacter->GetActorLocation(), FQuat::Identity, ECC_Pawn, Sphere);
	float BestDistSq = LockOnRadius * LockOnRadius;
	for (FOverlapResult& Result : OverlapResult)
	{
		AActor* Actor = Result.GetActor();
		if (!Actor || Actor == OwnerCharacter) continue;

		if (TargetClass && !Actor->IsA(TargetClass)) continue;

		float DistSquared = FVector::DistSquared(OwnerCharacter->GetActorLocation(), Actor->GetActorLocation());
		if (DistSquared < BestDistSq)
		{
			BestDistSq = DistSquared;
			TargetActor = Actor;
		}
 	}
	

	return TargetActor;
}

void ULockOnTargetComponent::ClearTarget()
{
	CurrentTarget = nullptr;
}

void ULockOnTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentTarget && OwnerCharacter)
	{
		float DistSq = FVector::DistSquared(OwnerCharacter->GetActorLocation(), CurrentTarget->GetActorLocation());

		if (DistSq > Distance)
		{
			ClearTarget();
			return;
		}

		FVector ToTarget = CurrentTarget->GetActorLocation() - OwnerCharacter->GetActorLocation();

		ToTarget.Z = 0; // Ignore Pitch

		FRotator TargetRot = ToTarget.Rotation();
		FRotator CurrentRot = OwnerCharacter->GetActorRotation();

		FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, RotationSpeed);
		OwnerCharacter->SetActorRotation(NewRot);
	}
}


