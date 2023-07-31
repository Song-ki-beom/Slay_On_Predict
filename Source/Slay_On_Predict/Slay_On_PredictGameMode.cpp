// Copyright Epic Games, Inc. All Rights Reserved.

#include "Slay_On_PredictGameMode.h"
#include "Slay_On_PredictCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASlay_On_PredictGameMode::ASlay_On_PredictGameMode()
{
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Class'/Script/Slay_On_Predict.MyCharacter'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
