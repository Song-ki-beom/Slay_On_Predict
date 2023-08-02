// Fill out your copyright notice in the Description page of Project Settings.


#include "Card_FL.h"

FCardInfo UCard_FL::GetRandomCard(UDataTable* CardTable) {

	int32 NumRows = CardTable->GetRowNames().Num();
    if (NumRows <= 0)
    {
        return FCardInfo(); 
    }

    // 랜덤한 인덱스를 생성합니다.
    int32 RandomIndex = FMath::RandRange(0, NumRows - 1);
    FName RandomRowName = CardTable->GetRowNames()[RandomIndex];
	FCardInfo* SelectedCard = CardTable->FindRow<FCardInfo>(RandomRowName, "");
    return *SelectedCard;
}



