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
}

void AFloorTriggerBox::BeginPlay() {
    Super::BeginPlay();
    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Green, true, -1, 0, 5);
}

void AFloorTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) {
    if (OtherActor && (OtherActor != this) && OtherActor->GetClass() == APawnForExplore::StaticClass()) {
        print("Overlap Begin");
        if (!Cast<APawnForExplore>(OtherActor)->IsControlled()) {
            AUnrealEngine_ExploreGameModeBase* MyGameModeBase = Cast<AUnrealEngine_ExploreGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
            if (MyGameModeBase) {
                MyGameModeBase->DeactivatePawn(Cast<APawnForExplore>(OtherActor)->GetPawnIdx());
            }
        }
    }
}
