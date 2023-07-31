// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "MyCharacter.h"
ACombatGameMode::ACombatGameMode()
{

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClass(TEXT("Class'/Script/Slay_On_Predict.MyCharacter'"));
	if (PlayerPawnClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnClass.Class;
	}
}