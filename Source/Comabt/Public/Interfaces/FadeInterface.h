// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FadeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UFadeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMABT_API IFadeInterface
{
	GENERATED_BODY()

public:
	virtual void FadeIn() = 0;
	virtual void FadeOut() = 0;
};
