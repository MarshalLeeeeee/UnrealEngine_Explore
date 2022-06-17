// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnForExplore.h"
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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeAsset.Succeeded()) {
		PawnMeshComponent->SetStaticMesh(CubeAsset.Object);
	}
	PawnMeshComponent->SetSimulatePhysics(true);
	PawnMeshComponent->SetEnableGravity(false);
	PawnMeshComponent->SetAngularDamping(10.0f);
	PawnMeshComponent->SetLinearDamping(5.0f);

	SpringBaseOffset = FVector(-100.0f, 0.0f, 0.0f);
	PawnSpringArm = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("PawnSpringArm"));
	PawnSpringArm->SetupAttachment(PawnMeshComponent);
	PawnSpringArm->TargetArmLength = 200.0f;
	PawnSpringArm->bUsePawnControlRotation = true;

	PawnCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	PawnCamera->SetupAttachment(PawnSpringArm);
	PawnCamera->bUsePawnControlRotation = true;

	bIsControl = true;
	bGrabing = false;
	bGrowing = false;
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

	float CurrentScale = PawnMeshComponent->GetComponentScale().X;
	if (bGrowing) CurrentScale += DeltaTime;
	else CurrentScale -= DeltaTime;
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	PawnMeshComponent->SetWorldScale3D(FVector(CurrentScale));

	AController* Ctrl = GetController();
	if (Ctrl) {
		PawnSpringArm->TargetOffset = Ctrl->GetControlRotation().RotateVector(SpringBaseOffset);
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

	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &APawnForExplore::StartGrow);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &APawnForExplore::StopGrow);
	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &APawnForExplore::StartGrab);
	PlayerInputComponent->BindAction("Grab", IE_Released, this, &APawnForExplore::StopGrab);
	PlayerInputComponent->BindAction("Control", IE_Released, this, &APawnForExplore::Control);

}

void APawnForExplore::MoveForward(float AxisValue) {
	if (!bIsControl) return;
	AController* Ctrl = GetController();
	if (Ctrl) {
		FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Ctrl->GetControlRotation());
		PawnMeshComponent->AddImpulse(ForwardVector * 10000.0f * AxisValue);
	}
	
}

void APawnForExplore::MoveRight(float AxisValue) {
	if (!bIsControl) return;
	AController* Ctrl = GetController();
	if (Ctrl) {
		FVector RightVector = UKismetMathLibrary::GetRightVector(Ctrl->GetControlRotation());
		PawnMeshComponent->AddImpulse(RightVector * 10000.0f * AxisValue);
	}
	
}

void APawnForExplore::MoveUp(float AxisValue) {
	if (!bIsControl) return;
	AController* Ctrl = GetController();
	if (Ctrl) {
		FVector UpVector = UKismetMathLibrary::GetUpVector(Ctrl->GetControlRotation());
		PawnMeshComponent->AddImpulse(UpVector * 10000.0f * AxisValue);
	}
	
}

void APawnForExplore::Turn(float AxisValue) {
	if (!bIsControl) return;
	AController* Ctrl = GetController();
	if (Ctrl) {
		float dt = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
		if (bGrabing) {
			FVector UpVector = UKismetMathLibrary::GetUpVector(Ctrl->GetControlRotation());
			PawnMeshComponent->AddAngularImpulseInRadians(UpVector * (AxisValue * 500000.0f));
		}
		else {
			AddControllerYawInput(AxisValue * dt * 50.0f);
		}
	}
}

void APawnForExplore::LookUp(float AxisValue) {
	if (!bIsControl) return;
	AController* Ctrl = GetController();
	if (Ctrl) {
		float dt = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
		if (bGrabing) {
			FVector RightVector = UKismetMathLibrary::GetRightVector(Ctrl->GetControlRotation());
			PawnMeshComponent->AddAngularImpulseInRadians(RightVector * (AxisValue * 500000.0f));
		}
		else {
			AddControllerPitchInput(AxisValue * dt * 50.0f);
		}
	}
}

void APawnForExplore::StartGrow() {
	if (!bIsControl) return;
	bGrowing = true;
}

void APawnForExplore::StopGrow() {
	if (!bIsControl) return;
	bGrowing = false;
}

void APawnForExplore::StartGrab() {
	if (!bIsControl) return;
	bGrabing = true;
}

void APawnForExplore::StopGrab() {
	if (!bIsControl) return;
	bGrabing = false;
}

void APawnForExplore::Control() {
	if (bIsControl) {
		PawnMeshComponent->SetEnableGravity(true);
		bIsControl = false;
	}
	else {
		PawnMeshComponent->SetEnableGravity(false);
		bIsControl = true;
	}
}

