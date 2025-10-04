// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ListenModeComponent.h"

#include "GameFramework/Character.h"
#include "Interfaces/FadeInterface.h"
#include "Kismet/GameplayStatics.h"


UListenModeComponent::UListenModeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UListenModeComponent::BeginPlay()
{
	Super::BeginPlay();

	ListenPostProcessVolume = Cast<APostProcessVolume>(UGameplayStatics::GetActorOfClass(GetWorld(), APostProcessVolume::StaticClass()));
	
}

void UListenModeComponent::ActivateListenMode()
{
	if (bIsListening || !ListenPostProcessVolume) return;

	bIsListening = true;

	FPostProcessSettings CurrentPostProcessSettings = ListenPostProcessVolume->Settings;

	CurrentPostProcessSettings.bOverride_ColorSaturation = true;
	CurrentPostProcessSettings.ColorSaturation = FVector4(0.2f, 0.2f, 0.2f, 1.0f);
	CurrentPostProcessSettings.bOverride_ColorGain = true;
	CurrentPostProcessSettings.ColorGain = FVector4(1.2f, 1.2f, 1.2f, 1.0f);

	CurrentPostProcessSettings.bOverride_SceneColorTint = true;
	CurrentPostProcessSettings.SceneColorTint = FLinearColor(0.85f, 0.85f, 0.85f, 1.0f);
	if (OutLineMaterial)
	{
		ListenPostProcessVolume->Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1.0f, OutLineMaterial));
	}

	ListenPostProcessVolume->Settings = CurrentPostProcessSettings;
	ListenPostProcessVolume->BlendWeight = 1.0f;

	GetWorld()->GetTimerManager().SetTimer(ListenHandle, this, &ThisClass::PerformListenScan, 0.2f, true);
}

void UListenModeComponent::DeactivateListenMode()
{
	if (!bIsListening || !ListenPostProcessVolume) return;

	bIsListening = false;
	ListenPostProcessVolume->BlendWeight = 0.0f;

	GetWorld()->GetTimerManager().ClearTimer(ListenHandle);
	ClearHighlight();
}



void UListenModeComponent::PerformListenScan()
{
	TArray<AActor*> FoundActors;
	TArray<AActor*> FadeActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FadeActors);

	for (AActor* Actor : FadeActors)
	{
		if (Actor->Implements<UFadeInterface>())
		{
			Cast<IFadeInterface>(Actor)->FadeIn();
		}
	}
	
	for (AActor* Actor : FoundActors)
	{
		if (Actor == GetOwner()) continue;

		float Distance = FVector::Dist(GetOwner()->GetActorLocation(), Actor->GetActorLocation());
		if (Distance <= ListenRadius)
		{
			HighlightEnemy(Actor);
		}
	}
 }

void UListenModeComponent::HighlightEnemy(AActor* Enemy)
{
	TArray<UMeshComponent*> Meshes;
	Enemy->GetComponents<UMeshComponent>(Meshes);

	for (UMeshComponent* Mesh : Meshes)
	{
		if (Mesh)
		{
			Mesh->SetRenderCustomDepth(true);
			Mesh->SetCustomDepthStencilValue(251);
		}
	}
}

void UListenModeComponent::ClearHighlight()
{
	TArray<AActor*> FoundActors;
	TArray<AActor*> FadeActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FadeActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundActors);
	for (AActor* Actor : FadeActors)
	{
		if (Actor->Implements<UFadeInterface>())
		{
			Cast<IFadeInterface>(Actor)->FadeOut();
		}
	}
	
	for (AActor* Actor : FoundActors)
	{
		TArray<UMeshComponent*> Meshes;
		Actor->GetComponents<UMeshComponent>(Meshes);

		for (UMeshComponent* Mesh : Meshes)
		{
			if (Mesh)
			{
				Mesh->SetRenderCustomDepth(false);
			}
		}
	}
}



