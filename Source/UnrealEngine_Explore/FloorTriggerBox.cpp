// Fill out your copyright notice in the Description page of Project Settings.
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

#include "FloorTriggerBox.h"
#include "UnrealEngine_ExploreGameModeBase.h"
#include "PawnForExplore.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

AFloorTriggerBox::AFloorTriggerBox() {
    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &AFloorTriggerBox::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AFloorTriggerBox::OnOverlapEnd);

    CurrentTriggeredPawn = nullptr;
}

void AFloorTriggerBox::BeginPlay() {
    Super::BeginPlay();
    
    // DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Green, true, -1, 0, 5);
}

void AFloorTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) {
    if (OtherActor && (OtherActor != this) && OtherActor->GetClass() == APawnForExplore::StaticClass()) {
        if (!Cast<APawnForExplore>(OtherActor)->IsControlled()) {
            Cast<APawnForExplore>(OtherActor)->ReadyToDestroy();
        }
        else CurrentTriggeredPawn = OtherActor;
    }
}

void AFloorTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor) {
    if (OtherActor && (OtherActor != this) && OtherActor->GetClass() == APawnForExplore::StaticClass()) {
        if (Cast<APawnForExplore>(OtherActor)->IsControlled()) {
            CurrentTriggeredPawn = nullptr;
        }
    }
}

void AFloorTriggerBox::IsCurrentPawnInTrigger() {
    if (CurrentTriggeredPawn) {
        Cast<APawnForExplore>(CurrentTriggeredPawn)->ReadyToDestroy();
        CurrentTriggeredPawn = nullptr;
    }
}
