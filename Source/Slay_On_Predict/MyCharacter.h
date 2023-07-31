// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class SLAY_ON_PREDICT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;


public:
	// Sets default values for this character's properties
	AMyCharacter();
	void UpDown(float Value);
	void LeftRight(float Value);
	float GetLeftRightValue() { return LeftRightValue; };
	float GetUpDownValue() { return UpDownValue; };
	/*void Yaw(float Value);*/
	void Attack();
	void AttackCheck();
	void HandleWallCollision();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	FName GetAttackMontageName();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	
	/*UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Weapon;
	UPROPERTY(VisibleAnywhere)
		class UMyStatComponent* Stat;
	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* HpBar;*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		float DefaultFOV;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		float ZoomedFOV;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		float ZoomInterpSpeed;
	

private:

	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;


	UPROPERTY()
		class UMyAnimInstance* AnimInstance;

	UPROPERTY()
		int32 AttackIndex = 0;
	UPROPERTY()
		float LeftRightValue = 0;

	UPROPERTY()
		float UpDownValue = 0;
	UPROPERTY(VisibleAnywhere, Category = Pawn)
		bool IsAttacking = false;



	
};
