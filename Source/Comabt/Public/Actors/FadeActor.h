// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/FadeInterface.h"
#include "FadeActor.generated.h"

UCLASS()
class COMABT_API AFadeActor : public AActor, public IFadeInterface
{
	GENERATED_BODY()

public:
	AFadeActor();
	virtual void Tick(float DeltaTime) override;
	virtual void FadeIn() override;
	virtual void FadeOut() override;
	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Fade")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;

	float CurrentFade;

	float TargetFade;

	UPROPERTY(EditAnywhere, Category="Fade")
	float FadeSpeed = 1.0f;

	void UpdateFade(float DeltaTime);
};
