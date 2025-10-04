// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ListenModeComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COMABT_API UListenModeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UListenModeComponent();

	UFUNCTION(BlueprintCallable, Category="ListenMode")
	void ActivateListenMode();

	UFUNCTION(BlueprintCallable, Category="ListenMode")
	void DeactivateListenMode();
	
	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Listen Mode")
	bool bIsListening = false;

	UPROPERTY(VisibleAnywhere, Category="Listen Mode")
	float ListenRadius = 1200.f;

	UPROPERTY(EditAnywhere, Category="Listen Mode")
	UMaterialInterface* OutLineMaterial;

	FTimerHandle ListenHandle;
	
	void PerformListenScan();

	void HighlightEnemy(AActor* Enemy);

	void ClearHighlight();

	UPROPERTY()
	APostProcessVolume* ListenPostProcessVolume;
	
};
