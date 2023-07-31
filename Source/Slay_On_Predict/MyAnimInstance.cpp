// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyCharacter.h"
#include "DelegateManager.h"
#include "UObject/ConstructorHelpers.h"
UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animation/Character_ATk_Montage.Character_ATk_Montage'"));
	if (AM.Succeeded())
		AttackMontage = AM.Object;
}

void UMyAnimInstance::PlayAttackMontage()
{
	
		Montage_Play(AttackMontage, 1.f);
	

}

//void UMyAnimInstance::JumpToSection(int32 SectionIndex)
//{
//	FName Name = GetAttackMontageName(SectionIndex);
//	Montage_JumpToSection(Name, AttackMontage);
//}
//
//FName UMyAnimInstance::GetAttackMontageName(int32 SectionIndex)
//{
//
//	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
//}
//
void UMyAnimInstance::AnimNotify_AttackHit() // UNREAL'S NOTIFY GRAMMAR..FIND 'AttackHit' notify occured
{

	DelegateManager::OnAttackHit.Broadcast();
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds) //���� ��������� ���� ���������� ȣ��Ǵ� �Լ�, �� �����Ӹ��� ȣ��
{
	
	
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size(); // �ӵ� ������ 

		auto Character = Cast<AMyCharacter>(Pawn);
		Vertical = Character->GetUpDownValue();
		Horizontal = Character->GetLeftRightValue();
		if (Character) {
			SetIsFalling( Character->GetMovementComponent()->IsFalling());
		}
	}

}