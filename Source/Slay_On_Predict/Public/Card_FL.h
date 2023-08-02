// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStructs.h"
#include "Engine/DataTable.h"
#include "Blueprint/UserWidget.h"
#include "Card_FL.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SLAY_ON_PREDICT_API UCard_FL  :public UUserWidget
{
	GENERATED_BODY()

public:
		UFUNCTION()
		FCardInfo GetRandomCard(UDataTable* CardTable);


};



