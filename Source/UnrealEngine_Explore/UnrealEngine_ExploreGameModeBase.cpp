// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealEngine_ExploreGameModeBase.h"
#include "PawnForExplore.h"
#include "Kismet/GameplayStatics.h"

// Define constructor
AUnrealEngine_ExploreGameModeBase::AUnrealEngine_ExploreGameModeBase() {
	DefaultPawnClass = APawnForExplore::StaticClass();
	PawnCnt = 4;
	CurrPawnIdx = 0;
}

void AUnrealEngine_ExploreGameModeBase::BeginPlay() {
	for (int i = 0; i < PawnCnt; i++) {
		GamePawns.Push(GetWorld()->SpawnActor<APawnForExplore>(FVector((i + 1) * 500.0f), FRotator(0.0f, 0.0f, 0.0f)));
	}
	UGameplayStatics::GetPlayerController(GetWorld(),0)->Possess(GamePawns[3]);
}