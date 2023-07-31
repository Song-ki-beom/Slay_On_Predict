// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CardEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UCardEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLAY_ON_PREDICT_API ICardEventInterface
{
	GENERATED_BODY()
		void AddCard();
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:

};
