// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnemy_Character.generated.h"

UCLASS()
class SLAY_ON_PREDICT_API AMyEnemy_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEnemy_Character();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetLeftRightValue() { return LeftRightValue; };
	float GetUpDownValue() { return UpDownValue; };
	UFUNCTION()
		void OnHitByAtkMontageEnded(UAnimMontage* Montage, bool bInterrupted);
private:
	void HitByAttack();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
public:	

	UPROPERTY()
		class UEnemyAnimInstance* AnimInstance;
/*	UPROPERTY(VisibleAnywhere)
		class UMyStatComponent* Stat;
	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* HpBar; */
	
private:
	
	UPROPERTY()
		float LeftRightValue = 0;
	UPROPERTY()
		float UpDownValue = 0;
	

};
