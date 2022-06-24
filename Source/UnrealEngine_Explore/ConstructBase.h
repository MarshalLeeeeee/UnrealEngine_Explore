// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructBase.generated.h"

UCLASS()
class UNREALENGINE_EXPLORE_API AConstructBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConstructBase();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	USceneComponent* Anchor;
	class UCameraComponent* CameraComp;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateAnchorYaw(float DeltaYaw);
	void UpdateAnchorPitch(float DeltaPitch);

private:
	
	float anchorRoll;
	float anchorYaw;
	float anchorPitch;
};
