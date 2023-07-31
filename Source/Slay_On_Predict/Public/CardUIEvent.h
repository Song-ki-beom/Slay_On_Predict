// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyStructs.h"
#include "CardUIEvent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SLAY_ON_PREDICT_API UCardUIEvent : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "HUD")
		void AddCard(UUserWidget* DeckBtn);
public:
	UPROPERTY(EditAnywhere)
		FCardInfo cardInfo;

};
