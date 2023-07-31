// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Components/TextBlock.h"
#include "Math/Color.h"
#include "MyStructs.generated.h"

/**
 * 
 */
class SLAY_ON_PREDICT_API MyStructs
{
public:
	MyStructs();
	~MyStructs();
};

USTRUCT(Atomic, BlueprintType)
struct FCardInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* CardName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* CardDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor BackGroundImage;



};