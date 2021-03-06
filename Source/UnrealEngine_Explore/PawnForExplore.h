// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnForExplore.generated.h"


UCLASS()
class UNREALENGINE_EXPLORE_API APawnForExplore : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnForExplore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PawnMeshComponent;

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* PawnSpringArm;

	UPROPERTY(EditAnywhere)
		FVector SpringBaseOffset;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* PawnCamera;

	class UNiagaraSystem* PawnDestroyEffect;
	FTimerHandle PawnDestroyTimerHandle;
	float PawnDestroyInterval;
	void ReadyToDestroy();
	void PawnDestroyTimer();


	// control function
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void MoveUp(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void Zoom(float AxisValue);
	void StartGrab();
	void StopGrab();
	void Control();
	void Pause();

	// state function
	void Init(UStaticMesh* mesh, class UMaterialInstanceDynamic* materialInstance, int i);
	bool IsControlled();
	bool IsDestroying();
	int GetPawnIdx();
	

	void SetCollision(ECollisionEnabled::Type NewType);


protected:

	float armLength;
	float impulseCoef;
	float angularImpulseCoef;

	float releaseControlTime;
	float destroyHeight;

	bool bIsControl;
	bool bGrabing;
	bool bInit;
	bool bDestroy;
	
	int pawnIdx;
};
