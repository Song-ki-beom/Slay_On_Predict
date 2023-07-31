// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
DECLARE_MULTICAST_DELEGATE(FOnAttackHit);
/**
 * 
 */
class SLAY_ON_PREDICT_API DelegateManager
{
public:
	static FOnAttackHit OnAttackHit;
	DelegateManager();
	~DelegateManager();
};
