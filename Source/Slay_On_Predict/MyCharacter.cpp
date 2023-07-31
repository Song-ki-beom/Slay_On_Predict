// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CollisionQueryParams.h"
#include "MyAnimInstance.h"
#include "DelegateManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "Animation/AnimBlueprint.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonYin/Characters/Heroes/Yin/Meshes/Yin.Yin'"));
	//Spawn Mesh
	if (SM.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SM.Object); // character.h�� mesh �� private �̹ƿ� mesh �� �������� getmesh() �� ����ͽ� �����´�.
	}
	//Spawn SpringArm And relocate
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->SetRelativeLocation(FVector(150.f, 20.f, 0.f));
	SpringArm->SetRelativeRotation(FRotator(-7.f, -30.f, 0.f));
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	
	
	//Set Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	// Set default FOV and zoomed FOV values
	DefaultFOV = 90.0f;
	ZoomedFOV = 60.0f;
	// Set zoom interpolation speed
	ZoomInterpSpeed = 10.0f;



	//Animation Setup
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBP(TEXT("AnimBlueprint'/Game/Animation/Character_BP_ANIM.Character_BP_ANIM'"));
	if (AnimBP.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("Anim Ins Set Success"));

		GetMesh()->SetAnimInstanceClass(AnimBP.Object->GeneratedClass);
	}
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set the initial FOV value to the default FOV
	Camera->SetFieldOfView(DefaultFOV);
	//GetAnimInstance as variable
	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance()); // Should add instance in BeginPlay because getmesh is added in editor through constructor , not instantiated in Constructor
	if (AnimInstance)
	{
		DelegateManager::OnAttackHit.AddUObject(this, &AMyCharacter::AttackCheck);
		UE_LOG(LogTemp, Log, TEXT("CharacterAnim Ins Load Success"));
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);
		
	}
	
		
		


	
	
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleWallCollision();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown); //��(axis)�� �Լ��� binding 
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	//PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);


}
//LINE TRACE forward 100.f length from the camera, once collision catch in HitResult,
//Change FOV BY INTERPOLATION
void AMyCharacter::HandleWallCollision()
{
	FVector CameraLocation = Camera->GetComponentLocation();
	FVector ForwardVector = Camera->GetForwardVector();

	FHitResult HitResult;
	FVector EndTrace = CameraLocation + ForwardVector * 100.0f; // Line trace length..

	//Line trace Start
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndTrace, ECC_Visibility);

	if (bHit) //collision detected
	{
		// If a collision is detected, interpolate the FOV value to the zoomed FOV
		float TargetFOV = ZoomedFOV;
		float NewFOV = FMath::FInterpTo(Camera->FieldOfView, TargetFOV, GetWorld()->GetDeltaSeconds(), ZoomInterpSpeed);
		Camera->SetFieldOfView(NewFOV);
	}
	else
	{
		// If no collision, interpolate the FOV value back to the default FOV
		float TargetFOV = DefaultFOV;
		float NewFOV = FMath::FInterpTo(Camera->FieldOfView, TargetFOV, GetWorld()->GetDeltaSeconds(), ZoomInterpSpeed);
		Camera->SetFieldOfView(NewFOV);
	}
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//Stat->OnAttacked(DamageAmount);
	return 0.0f;
}

void AMyCharacter::UpDown(float Value)
{

	UpDownValue = Value;
	AddMovementInput(GetActorForwardVector(), Value);
	
	
}

void AMyCharacter::LeftRight(float Value)
{
	if (Value == 0.f)
		return;
	LeftRightValue = Value;
	AddMovementInput(GetActorRightVector(), Value);

	
}

//void AMyCharacter::Yaw(float Value) {
//	AddControllerYawInput(Value);
//}

void AMyCharacter::Attack()
{
	if (IsAttacking)
		return;
	if(AnimInstance)
		AnimInstance->PlayAttackMontage();
	//AnimInstance->JumpToSection(AttackIndex);
	//AttackIndex = (AttackIndex + 1) % 3;
	IsAttacking = true;
}

void AMyCharacter::AttackCheck()
{
	/*FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	float AttackRange = 100.f;
	float AttackRadius = 50.f;

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);


	FVector Vec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + Vec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor;
	if (bResult)
		DrawColor = FColor::Green;
	else
		DrawColor = FColor::Red;


	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius,
		Rotation, DrawColor, false, 2.f);

	if (bResult && HitResult.Actor.IsValid()) {
		UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *HitResult.Actor->GetName());

		FDamageEvent DamageEvent;
		HitResult.Actor->TakeDamage(Stat->GetAttack(), DamageEvent, GetController(), this);
*/
	}







void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}


