// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "UnrealEngine_ExploreGameModeBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UPauseMenu::NativeConstruct() {
	Super::NativeConstruct();

	FScriptDelegate RestartButtonDelegte;
	RestartButtonDelegte.BindUFunction(this, "RestartGame");
	RestartButton->OnClicked.Add(RestartButtonDelegte);

	FScriptDelegate RestartButtonHoveredDelegte;
	RestartButtonHoveredDelegte.BindUFunction(this, "OnHovered");
	RestartButton->OnHovered.Add(RestartButtonHoveredDelegte);

	FScriptDelegate RestartButtonUnhoveredDelegte;
	RestartButtonUnhoveredDelegte.BindUFunction(this, "OnUnhovered");
	RestartButton->OnUnhovered.Add(RestartButtonUnhoveredDelegte);

	FScriptDelegate ResumeButtonDelegte;
	ResumeButtonDelegte.BindUFunction(this, "ResumeGame");
	ResumeButton->OnClicked.Add(ResumeButtonDelegte);

	FScriptDelegate ResumeButtonHoveredDelegte;
	ResumeButtonHoveredDelegte.BindUFunction(this, "OnHovered");
	ResumeButton->OnHovered.Add(ResumeButtonHoveredDelegte);

	FScriptDelegate ResumeButtonUnhoveredDelegte;
	ResumeButtonUnhoveredDelegte.BindUFunction(this, "OnUnhovered");
	ResumeButton->OnUnhovered.Add(ResumeButtonUnhoveredDelegte);

	FScriptDelegate QuitButtonDelegte;
	QuitButtonDelegte.BindUFunction(this, "QuitGame");
	QuitButton->OnClicked.Add(QuitButtonDelegte);

	FScriptDelegate QuitButtonHoveredDelegte;
	QuitButtonHoveredDelegte.BindUFunction(this, "OnHovered");
	QuitButton->OnHovered.Add(QuitButtonHoveredDelegte);

	FScriptDelegate QuitButtonUnhoveredDelegte;
	QuitButtonUnhoveredDelegte.BindUFunction(this, "OnUnhovered");
	QuitButton->OnUnhovered.Add(QuitButtonUnhoveredDelegte);
}

void UPauseMenu::RestartGame() {
	AUnrealEngine_ExploreGameModeBase* MyGameModeBase = Cast<AUnrealEngine_ExploreGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MyGameModeBase) MyGameModeBase->RestartGame();
}

void UPauseMenu::ResumeGame() {
	AUnrealEngine_ExploreGameModeBase* MyGameModeBase = Cast<AUnrealEngine_ExploreGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MyGameModeBase) MyGameModeBase->PauseGame();
}

void UPauseMenu::QuitGame() {
	AUnrealEngine_ExploreGameModeBase* MyGameModeBase = Cast<AUnrealEngine_ExploreGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MyGameModeBase) MyGameModeBase->QuitGame();
}

void UPauseMenu::OnHovered() {
	if (ResumeButton->IsHovered()) {
		ResumeButton->SetBackgroundColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
	}
	if (RestartButton->IsHovered()) {
		RestartButton->SetBackgroundColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
	}
	if (QuitButton->IsHovered()) {
		QuitButton->SetBackgroundColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
	}
}

void UPauseMenu::OnUnhovered() {
	if (!ResumeButton->IsHovered()) {
		ResumeButton->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (!RestartButton->IsHovered()) {
		RestartButton->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (!QuitButton->IsHovered()) {
		QuitButton->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
