// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

//DECLARE_MULTICAST_DELEGATE(FOnAttackHit);

/**
 * 
 */
UCLASS()
class SLAY_ON_PREDICT_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "EnemyAnimFunctions")
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	UEnemyAnimInstance();
	void SetIsFalling(bool IsFallingg) { this->IsFalling = IsFallingg;};
	bool GetIsHit() { return IsHit; };
	void SetIsHit(bool isHitt) { this->IsHit = isHitt; };
	void PlayHitByAtkMontage();

	//void PlayAttackMontage();

	//void JumpToSection(int32 SectionIndex);
	//FName GetAttackMontageName(int32 SectionIndex);
private:
	UFUNCTION()
		void AnimNotify_HitByAttack();

public:
	
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsFalling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		UAnimMontage* HitByAtkMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float Horizontal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float Vertical;
};
