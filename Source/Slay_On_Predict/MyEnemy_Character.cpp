// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CollisionQueryParams.h"
#include "EnemyAnimInstance.h"
#include "DelegateManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Animation/AnimBlueprint.h"

// Sets default values
AMyEnemy_Character::AMyEnemy_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AM(TEXT("SkeletalMesh'/Game/ParagonRampage/Characters/Heroes/Rampage/Meshes/Rampage.Rampage'"));
	//Spawn Mesh
	if (AM.Succeeded()) {
		GetMesh()->SetSkeletalMesh(AM.Object); // character.h�� mesh �� private �̹ƿ� mesh �� �������� getmesh() �� ����ͽ� �����´�.
	}
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -90.f), FRotator(0.f, 0.f, 0.f));


	//Animation Setup
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> EAnimBP(TEXT("AnimBlueprint'/Game/Animation/Enemy_BP_ANIM.Enemy_BP_ANIM'"));
	if (EAnimBP.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("Enemy Anim Ins Set Success##"));

		GetMesh()->SetAnimInstanceClass(EAnimBP.Object->GeneratedClass);
	}
}



// Called when the game starts or when spawned
void AMyEnemy_Character::BeginPlay()
{
	Super::BeginPlay();
	//GetAnimInstance as variable
	AnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance()); // Should add instance in BeginPlay because getmesh is added in editor through constructor , not instantiated in Constructor
	if (AnimInstance)
	{
		DelegateManager::OnAttackHit.AddUObject(this, &AMyEnemy_Character::HitByAttack);
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMyEnemy_Character::OnHitByAtkMontageEnded);

		UE_LOG(LogTemp, Log, TEXT("EnemyAnim Ins Load Success"));
		
	}
}

void AMyEnemy_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

// Called every frame
void AMyEnemy_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}void AMyEnemy_Character::HitByAttack()
{
	if (!AnimInstance->GetIsHit()) {
		AnimInstance->SetIsHit(true);
		AnimInstance->PlayHitByAtkMontage();
		
	}
}




// Called to bind functionality to input
void AMyEnemy_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyEnemy_Character::OnHitByAtkMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	AnimInstance ->SetIsHit(false);
}