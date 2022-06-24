// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnForExplore.h"
#include "UnrealEngine_ExploreGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnForExplore::APawnForExplore()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PawnMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMeshComponent"));
	PawnMeshComponent->SetupAttachment(RootComponent);

	armLength = 500.f;
	SpringBaseOffset = FVector(-100.0f, 0.0f, 0.0f);
	PawnSpringArm = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("PawnSpringArm"));
	PawnSpringArm->SetupAttachment(PawnMeshComponent);
	PawnSpringArm->TargetArmLength = armLength;
	PawnSpringArm->bUsePawnControlRotation = true;
	
	PawnCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	PawnCamera->SetupAttachment(PawnSpringArm);
	PawnCamera->bUsePawnControlRotation = true;

	bIsControl = false;
	bGrabing = false;
	impulseCoef = 1.0;
	angularImpulseCoef = 1.0;
}

// Called when the game starts or when spawned
void APawnForExplore::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APawnForExplore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AController* Ctrl = GetController();
	if (Ctrl) {
		PawnSpringArm->TargetOffset = Ctrl->GetControlRotation().RotateVector(SpringBaseOffset);
		
		if (!bIsControl) {
			float currT = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
			AUnrealEngine_ExploreGameModeBase* MyGameModeBase = Cast<AUnrealEngine_ExploreGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			if (MyGameModeBase && MyGameModeBase->AllPawnStatic() && currT-releaseControlTime > 2.0f) MyGameModeBase->SwitchPawn();
		}
	}
}

// Called to bind functionality to input
void APawnForExplore::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APawnForExplore::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APawnForExplore::MoveRight);
	PlayerInputComponent->BindAxis("Up", this, &APawnForExplore::MoveUp);
	PlayerInputComponent->BindAxis("LookUp", this, &APawnForExplore::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &APawnForExplore::Turn);
	PlayerInputComponent->BindAxis("Zoom", this, &APawnForExplore::Zoom);

	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &APawnForExplore::StartGrab);
	PlayerInputComponent->BindAction("Grab", IE_Released, this, &APawnForExplore::StopGrab);
	PlayerInputComponent->BindAction("Control", IE_Released, this, &APawnForExplore::Control);

}

void APawnForExplore::MoveForward(float AxisValue) {
	AController* Ctrl = GetController();
	if (Ctrl) {
		if (bIsControl) {
			FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Ctrl->GetControlRotation());
			PawnMeshComponent->AddImpulse(ForwardVector * 100.0f * impulseCoef * AxisValue * PawnMeshComponent->GetMass());
		}
		
	}
	
}

void APawnForExplore::MoveRight(float AxisValue) {
	AController* Ctrl = GetController();
	if (Ctrl) {
		if (bIsControl) {
			FVector RightVector = UKismetMathLibrary::GetRightVector(Ctrl->GetControlRotation());
			PawnMeshComponent->AddImpulse(RightVector * 100.0f * impulseCoef * AxisValue * PawnMeshComponent->GetMass());
		}
		
	}
	
}

void APawnForExplore::MoveUp(float AxisValue) {
	AController* Ctrl = GetController();
	if (Ctrl) {
		if (bIsControl) {
			FVector UpVector = UKismetMathLibrary::GetUpVector(Ctrl->GetControlRotation());
			PawnMeshComponent->AddImpulse(UpVector * 100.0f * impulseCoef * AxisValue * PawnMeshComponent->GetMass());
		}
		
	}
	
}

void APawnForExplore::Turn(float AxisValue) {
	AController* Ctrl = GetController();
	if (Ctrl) {
		float dt = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
		if (bIsControl) {
			if (bGrabing) {
				FVector UpVector = UKismetMathLibrary::GetUpVector(Ctrl->GetControlRotation());
				PawnMeshComponent->AddAngularImpulseInRadians(UpVector * (AxisValue * angularImpulseCoef * 100000.0f * PawnMeshComponent->GetMass()));
			}
			else {
				AddControllerYawInput(AxisValue * dt * 50.0f);
			}
		}
		else {
			AUnrealEngine_ExploreGameModeBase* MyGameModeBase = Cast<AUnrealEngine_ExploreGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			if (MyGameModeBase) MyGameModeBase->UpdateViewYaw(AxisValue * dt * 50.0f);
		}
	}
}

void APawnForExplore::LookUp(float AxisValue) {
	AController* Ctrl = GetController();
	if (Ctrl) {
		float dt = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
		if (bIsControl) {
			if (bGrabing) {
				FVector RightVector = UKismetMathLibrary::GetRightVector(Ctrl->GetControlRotation());
				PawnMeshComponent->AddAngularImpulseInRadians(RightVector * (AxisValue * angularImpulseCoef * 100000.0f * PawnMeshComponent->GetMass()));
			}
			else {
				AddControllerPitchInput(AxisValue * dt * 50.0f);
			}
		}
		else {
			AUnrealEngine_ExploreGameModeBase* MyGameModeBase = Cast<AUnrealEngine_ExploreGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			if (MyGameModeBase) MyGameModeBase->UpdateViewPitch(AxisValue * dt * 50.0f);
		}
	}
}

void APawnForExplore::Zoom(float AxisValue) {
	AController* Ctrl = GetController();
	if (Ctrl) {
		if (bIsControl) {
			float dt = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
			armLength += dt * AxisValue * 1000.0f;
			armLength = FMath::Clamp(armLength, 100.0f, 500.0f);
			PawnSpringArm->TargetArmLength = armLength;
			impulseCoef += dt * AxisValue * 2.0f;
			impulseCoef = FMath::Clamp(impulseCoef, 0.2f, 1.0f);
			angularImpulseCoef += dt * AxisValue * 2.0f;
			angularImpulseCoef = FMath::Clamp(angularImpulseCoef, 0.2f, 1.0f);
		}
	}
	if (!bIsControl) return;
	
}

void APawnForExplore::StartGrab() {
	AController* Ctrl = GetController();
	if (Ctrl) {
		if (bIsControl) {
			bGrabing = true;
		}
	}
}

void APawnForExplore::StopGrab() {
	AController* Ctrl = GetController();
	if (Ctrl) {
		if (bIsControl) {
			bGrabing = false;
		}
	}
}

void APawnForExplore::Control() {
	AController* Ctrl = GetController();
	if (Ctrl) {
		if (bIsControl) {
			PawnMeshComponent->SetEnableGravity(true);
			PawnMeshComponent->SetAngularDamping(2.0f);
			PawnMeshComponent->SetLinearDamping(2.0f);
			bIsControl = false;
			releaseControlTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
			AUnrealEngine_ExploreGameModeBase* MyGameModeBase = Cast<AUnrealEngine_ExploreGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			if (MyGameModeBase) MyGameModeBase->SwitchView();
		}
	}
}

void APawnForExplore::Init(UStaticMesh* mesh) {
	SetActorLocation(FVector(500.0f,1000.0f,500.0f));
	PawnMeshComponent->SetStaticMesh(mesh);
	PawnMeshComponent->SetWorldScale3D(FVector(0.25f));
	PawnMeshComponent->SetSimulatePhysics(true);
	PawnMeshComponent->SetEnableGravity(false);
	PawnMeshComponent->SetAngularDamping(5.0f);
	PawnMeshComponent->SetLinearDamping(5.0f);
	bIsControl = true;
}

