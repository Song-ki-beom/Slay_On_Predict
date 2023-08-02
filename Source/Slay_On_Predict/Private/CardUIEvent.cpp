// Fill out your copyright notice in the Description page of Project Settings.


#include "CardUIEvent.h"
#include "Blueprint/UserWidget.h"	
#include "Engine/DataTable.h"
#include "Card_FL.h"
#include "UObject/ConstructorHelpers.h"
FCardInfo UCardUIEvent::AddCard(UDataTable* CardTable) {
	card_FL = NewObject<UCard_FL>();
	FCardInfo card = card_FL->GetRandomCard(CardTable);
	 
	return card;
	
	
}
