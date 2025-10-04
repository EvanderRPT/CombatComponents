// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FadeActor.h"


AFadeActor::AFadeActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

	CurrentFade = 1.0f;
	TargetFade = 1.0f;
}

void AFadeActor::BeginPlay()
{
	Super::BeginPlay();

	if (MeshComponent && MeshComponent->GetMaterial(0))
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(0), this);

		MeshComponent->SetMaterial(0, DynamicMaterial);
	}
	
}

void AFadeActor::UpdateFade(float DeltaTime)
{
	if (!DynamicMaterial) return;
	if (!FMath::IsNearlyEqual(CurrentFade, TargetFade, KINDA_SMALL_NUMBER))
	{
		CurrentFade = FMath::FInterpTo(CurrentFade, TargetFade, DeltaTime, FadeSpeed);
		DynamicMaterial->SetScalarParameterValue(TEXT("Fade"), CurrentFade);
	}
}

void AFadeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateFade(DeltaTime);
}

void AFadeActor::FadeIn()
{
	TargetFade = 0.0f;
}

void AFadeActor::FadeOut()
{
	TargetFade = 1.0f;
}

