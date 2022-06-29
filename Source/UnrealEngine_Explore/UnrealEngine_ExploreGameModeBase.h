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
	virtual void Tick(float DeltaTime) override;

	void SwitchPawn();
	void SwitchView(float blendTime);
	void UpdateViewYaw(float DeltaYaw);
	void UpdateViewPitch(float DeltaPitch);
	void UpdateViewDistance(float DeltaDist);
	bool AllPawnStatic();
	void ReadyToSwitch(float delay);
	void DeactivatePawn(int i);

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;

	bool bReadyToSwitch;
	float SwitchTime;

	int CurrPawnIdx;
	int PawnCnt;
	int LostPawnCnt;
	TArray<APawn*> GamePawns;
	TArray<UStaticMesh*> GamePawnMeshes;
	TArray<int> GamePawnIdxes;

	AActor* ConstructBase;

	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	/** The widget instance that we are using as our menu. */
	UPROPERTY()
		UUserWidget* CurrentWidget;
};
