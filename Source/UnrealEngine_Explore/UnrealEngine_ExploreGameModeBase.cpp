// Copyright Epic Games, Inc. All Rights Reserved.
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

#include "UnrealEngine_ExploreGameModeBase.h"
#include "PawnForExplore.h"
#include "ConstructBase.h"
#include "UserWidgetForExplore.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

// Define constructor
AUnrealEngine_ExploreGameModeBase::AUnrealEngine_ExploreGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = APawnForExplore::StaticClass();
	PawnCnt = 15;
	LostPawnCnt = 0;
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

	// static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Game/UI/Menus/GameMenu"));
	// StartingWidgetClass = WidgetAsset.Class;
}

void AUnrealEngine_ExploreGameModeBase::BeginPlay() {
	for (int i = 0; i < PawnCnt; i++) {
		GamePawns.Push(GetWorld()->SpawnActor<APawnForExplore>(FVector(-500.0f), FRotator(0.0f, 0.0f, 0.0f)));
	}
	GamePawns.Push(GetWorld()->SpawnActor<APawnForExplore>(FVector(-1000.0f), FRotator(0.0f, 0.0f, 0.0f))); // Ghost pawn for camera view
	Cast<APawnForExplore>(GamePawns[GamePawnIdxes[CurrPawnIdx]])->Init(GamePawnMeshes[GamePawnIdxes[CurrPawnIdx]], CurrPawnIdx);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(GamePawns[GamePawnIdxes[CurrPawnIdx]]);
	bReadyToSwitch = false;
	SwitchTime = -1.0f;

	ConstructBase = GetWorld()->SpawnActor<AConstructBase>(FVector(500.0f, 500.0f, 100.0f), FRotator(0.0f, 0.0f, 0.0f));

	ChangeMenuWidget(StartingWidgetClass);
}

void AUnrealEngine_ExploreGameModeBase::Tick(float DeltaTime) {
	if (bReadyToSwitch && AllPawnStatic() && UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld()) > SwitchTime) {
		SwitchPawn();
	}
}

void AUnrealEngine_ExploreGameModeBase::SwitchPawn() {
	while (++CurrPawnIdx < PawnCnt) {
		if (GamePawns[GamePawnIdxes[CurrPawnIdx]]) break;
	}
	if (CurrPawnIdx < PawnCnt) {
		Cast<APawnForExplore>(GamePawns[GamePawnIdxes[CurrPawnIdx]])->Init(GamePawnMeshes[GamePawnIdxes[CurrPawnIdx]], CurrPawnIdx);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(GamePawns[GamePawnIdxes[CurrPawnIdx]]);
	}
	else {
		UUserWidgetForExplore* GameWidget = Cast<UUserWidgetForExplore>(CurrentWidget);
		if (GameWidget) GameWidget->SetTestTitle(FText::FromString(TEXT("Game Over")));
	}
	bReadyToSwitch = false;
	SwitchTime = -1.0f;
}

void AUnrealEngine_ExploreGameModeBase::SwitchView(float blendTime) {
	APlayerController* GamePlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (GamePlayerController) {
		GamePlayerController->SetViewTargetWithBlend(ConstructBase, blendTime);
	}
}

void AUnrealEngine_ExploreGameModeBase::UpdateViewYaw(float DeltaYaw) {
	Cast<AConstructBase>(ConstructBase)->UpdateAnchorYaw(DeltaYaw);
}

void AUnrealEngine_ExploreGameModeBase::UpdateViewPitch(float DeltaPitch) {
	Cast<AConstructBase>(ConstructBase)->UpdateAnchorPitch(DeltaPitch);
}

void AUnrealEngine_ExploreGameModeBase::UpdateViewDistance(float DeltaDist) {
	Cast<AConstructBase>(ConstructBase)->UpdateAnchorDistance(DeltaDist);
}

bool AUnrealEngine_ExploreGameModeBase::AllPawnStatic() {
	for (int i = 0; i < PawnCnt; i++) {
		if (GamePawns[i]) {
			FVector v = Cast<APawnForExplore>(GamePawns[i])->PawnMeshComponent->GetComponentVelocity();
			if (!v.IsZero()) return false;
		}
	}
	return true;
}

void AUnrealEngine_ExploreGameModeBase::DeactivatePawn(int i) {
	if (i == CurrPawnIdx) {
		UUserWidgetForExplore* GameWidget = Cast<UUserWidgetForExplore>(CurrentWidget);
		if (GameWidget) GameWidget->SetTestTitle(FText::FromString(TEXT("Deactivate self")));
		ReadyToSwitch(1.0f);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(GamePawns[PawnCnt]);
		SwitchView(0.0f);
	}
	GetWorld()->DestroyActor(GamePawns[GamePawnIdxes[i]]);
	GamePawns[GamePawnIdxes[i]] = nullptr;
	LostPawnCnt++;
	UUserWidgetForExplore* GameWidget = Cast<UUserWidgetForExplore>(CurrentWidget);
	if (GameWidget) GameWidget->SetLostPawnCnt(LostPawnCnt);
}

void AUnrealEngine_ExploreGameModeBase::ReadyToSwitch(float delay) {
	bReadyToSwitch = true;
	SwitchTime = FMath::Max(SwitchTime, UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld()) + delay);
	UUserWidgetForExplore* GameWidget = Cast<UUserWidgetForExplore>(CurrentWidget);
	if (GameWidget) GameWidget->SetTestTitle(FText::FromString(TEXT("Ready to switch")));
}

void AUnrealEngine_ExploreGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}