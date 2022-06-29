// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructBase.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AConstructBase::AConstructBase() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UStaticMeshComponent* StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConstructBaseMeshComponent"));
	StaticMeshComp->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	StaticMeshComp->SetWorldScale3D(FVector(1.5f,1.5f,0.5f));

	Anchor = CreateDefaultSubobject<USceneComponent>(TEXT("ConstructBaseArmAnchor"));
	Anchor->SetupAttachment(RootComponent);
	anchorPitch = -90.0f;
	anchorYaw = 0.0f;
	anchorRoll = 0.0f;
	Anchor->SetRelativeRotation(FRotator(anchorPitch, anchorYaw, anchorRoll));

	anchorDistance = 1000.0f;
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("ConstructBaseCamera"));
	CameraComp->SetupAttachment(Anchor);
	CameraComp->SetRelativeLocation(FVector(-anchorDistance, 0.0f, 0.0f));
	
}

// Called when the game starts or when spawned
void AConstructBase::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AConstructBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	Anchor->SetRelativeRotation(FRotator(anchorPitch, anchorYaw, anchorRoll));
	CameraComp->SetRelativeLocation(FVector(-anchorDistance, 0.0f, 0.0f));
}

void AConstructBase::UpdateAnchorYaw(float DeltaYaw) {
	anchorYaw += DeltaYaw;
}

void AConstructBase::UpdateAnchorPitch(float DeltaPitch) {
	anchorPitch = FMath::Clamp(anchorPitch + DeltaPitch, -90.0f, -20.0f);
}

void AConstructBase::UpdateAnchorDistance(float DeltaDist) {
	anchorDistance = FMath::Clamp(anchorDistance + DeltaDist, 500.0f, 1000.0f);
}
