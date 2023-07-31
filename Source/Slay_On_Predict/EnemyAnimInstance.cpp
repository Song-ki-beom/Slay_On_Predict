// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyEnemy_Character.h"
#include "UObject/ConstructorHelpers.h"
UEnemyAnimInstance::UEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HM(TEXT("AnimMontage'/Game/Animation/Enemy_HIT_Montage.Enemy_HIT_Montage'"));
	if (HM.Succeeded())
		HitByAtkMontage = HM.Object;
}


//Play Hit Animation
void UEnemyAnimInstance::PlayHitByAtkMontage() 
{
	UE_LOG(LogTemp, Log, TEXT("PlayHitByAtkMontage!!!!!!"));

	Montage_Play(HitByAtkMontage, 1.f);


}

void UEnemyAnimInstance::AnimNotify_HitByAttack() // UNREAL'S NOTIFY GRAMMAR..FIND 'AttackHit' notify occured
{
	
	
}


//Play Attack Animation
//void UEnemyAnimInstance::AnimNotify_AttackHit()
//{
//
//	
//	//OnAttackHit.Broadcast();
//}


void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds) //���� ��������� ���� ���������� ȣ��Ǵ� �Լ�, �� �����Ӹ��� ȣ��
{


	Super::NativeUpdateAnimation(DeltaSeconds);
	
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size(); // �ӵ� ������ 

		auto Character = Cast<AMyEnemy_Character>(Pawn);
		Vertical = Character->GetUpDownValue();
		Horizontal = Character->GetLeftRightValue();
		if (Character) {
			SetIsFalling(Character->GetMovementComponent()->IsFalling());

		}
	}

}