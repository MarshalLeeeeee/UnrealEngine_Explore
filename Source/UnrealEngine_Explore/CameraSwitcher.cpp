// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSwitcher.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraSwitcher::ACameraSwitcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraSwitcher::BeginPlay()
{
	Super::BeginPlay();
	TimeToNextCameraChange = 0.0f;
    TimeBetweenCameraChanges = 2.0f;
    SmoothBlendTime = 0.75f;
}

// Called every frame
void ACameraSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    TimeToNextCameraChange -= DeltaTime;
    if (TimeToNextCameraChange <= 0.0f)
    {
        TimeToNextCameraChange += TimeBetweenCameraChanges;

        //Find the actor that handles control for the local player.
        APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
        if (OurPlayerController)
        {
            if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
            {
                //Cut instantly to camera one.
                OurPlayerController->SetViewTarget(CameraOne);
            }
            else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
            {
                //Blend smoothly to camera two.
                OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
            }
        }
    }
}

