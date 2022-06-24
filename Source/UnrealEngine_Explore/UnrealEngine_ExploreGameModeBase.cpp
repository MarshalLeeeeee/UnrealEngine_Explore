// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealEngine_ExploreGameModeBase.h"
#include "PawnForExplore.h"
#include "ConstructBase.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

// Define constructor
AUnrealEngine_ExploreGameModeBase::AUnrealEngine_ExploreGameModeBase() {
	DefaultPawnClass = APawnForExplore::StaticClass();
	PawnCnt = 15;
	CurrPawnIdx = 0;
	for (int i = 0; i < PawnCnt; i++) GamePawnIdxes.Emplace(i);
	for (int i = PawnCnt; i > 0; i--) {
		int j = FMath::RandHelper(i);
		int x = GamePawnIdxes[i - 1];
		GamePawnIdxes[i - 1] = GamePawnIdxes[j];
		GamePawnIdxes[j] = x;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset1(TEXT("/Game/Meshes/blockConcave.blockConcave"));
	GamePawnMeshes.Push(MeshAsset1.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset2(TEXT("/Game/Meshes/blockGroove.blockGroove"));
	GamePawnMeshes.Push(MeshAsset2.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset3(TEXT("/Game/Meshes/cone.cone"));
	GamePawnMeshes.Push(MeshAsset3.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset4(TEXT("/Game/Meshes/curvedBlock.curvedBlock"));
	GamePawnMeshes.Push(MeshAsset4.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset5(TEXT("/Game/Meshes/largePlane.largePlane"));
	GamePawnMeshes.Push(MeshAsset5.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset6(TEXT("/Game/Meshes/planeGroove.planeGroove"));
	GamePawnMeshes.Push(MeshAsset6.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset7(TEXT("/Game/Meshes/pyramid.pyramid"));
	GamePawnMeshes.Push(MeshAsset7.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset8(TEXT("/Game/Meshes/shipGroove.shipGroove"));
	GamePawnMeshes.Push(MeshAsset8.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset9(TEXT("/Game/Meshes/smallPlaneHole.smallPlaneHole"));
	GamePawnMeshes.Push(MeshAsset9.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset10(TEXT("/Game/Meshes/sphere.sphere"));
	GamePawnMeshes.Push(MeshAsset10.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset11(TEXT("/Game/Meshes/spindle.spindle"));
	GamePawnMeshes.Push(MeshAsset11.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset12(TEXT("/Game/Meshes/thickCylinder.thickCylinder"));
	GamePawnMeshes.Push(MeshAsset12.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset13(TEXT("/Game/Meshes/thickCylinderHole.thickCylinderHole"));
	GamePawnMeshes.Push(MeshAsset13.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset14(TEXT("/Game/Meshes/thinCylinder.thinCylinder"));
	GamePawnMeshes.Push(MeshAsset14.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset15(TEXT("/Game/Meshes/torus.torus"));
	GamePawnMeshes.Push(MeshAsset15.Object);
}

void AUnrealEngine_ExploreGameModeBase::BeginPlay() {
	for (int i = 0; i < PawnCnt; i++) {
		GamePawns.Push(GetWorld()->SpawnActor<APawnForExplore>(FVector(-500.0f), FRotator(0.0f, 0.0f, 0.0f)));
	}
	Cast<APawnForExplore>(GamePawns[GamePawnIdxes[CurrPawnIdx]])->Init(GamePawnMeshes[GamePawnIdxes[CurrPawnIdx]]);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(GamePawns[GamePawnIdxes[CurrPawnIdx]]);
	ConstructBase = GetWorld()->SpawnActor<AConstructBase>(FVector(500.0f, 500.0f, 100.0f), FRotator(0.0f, 0.0f, 0.0f));
}

void AUnrealEngine_ExploreGameModeBase::SwitchPawn() {
	CurrPawnIdx = (CurrPawnIdx + 1) % PawnCnt;
	Cast<APawnForExplore>(GamePawns[GamePawnIdxes[CurrPawnIdx]])->Init(GamePawnMeshes[GamePawnIdxes[CurrPawnIdx]]);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(GamePawns[GamePawnIdxes[CurrPawnIdx]]);
}

void AUnrealEngine_ExploreGameModeBase::SwitchView() {
	APlayerController* GamePlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (GamePlayerController) {
		GamePlayerController->SetViewTargetWithBlend(ConstructBase, 1.0f);
	}
}

void AUnrealEngine_ExploreGameModeBase::UpdateViewYaw(float DeltaYaw) {
	Cast<AConstructBase>(ConstructBase)->UpdateAnchorYaw(DeltaYaw);
}

void AUnrealEngine_ExploreGameModeBase::UpdateViewPitch(float DeltaPitch) {
	Cast<AConstructBase>(ConstructBase)->UpdateAnchorPitch(DeltaPitch);
}

bool AUnrealEngine_ExploreGameModeBase::AllPawnStatic() {
	for (int i = 0; i < PawnCnt; i++) {
		FVector v = Cast<APawnForExplore>(GamePawns[i])->PawnMeshComponent->GetComponentVelocity();
		if (!v.IsZero()) return false;
	}
	return true;
}