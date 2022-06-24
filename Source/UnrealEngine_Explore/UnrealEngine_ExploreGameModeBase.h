// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealEngine_ExploreGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALENGINE_EXPLORE_API AUnrealEngine_ExploreGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUnrealEngine_ExploreGameModeBase();

	void SwitchPawn();
	void SwitchView();
	void UpdateViewYaw(float DeltaYaw);
	void UpdateViewPitch(float DeltaPitch);
	bool AllPawnStatic();

protected:
	virtual void BeginPlay() override;

	int CurrPawnIdx;
	int PawnCnt;
	TArray<APawn*> GamePawns;
	TArray<UStaticMesh*> GamePawnMeshes;
	TArray<int> GamePawnIdxes;

	AActor* ConstructBase;
};
