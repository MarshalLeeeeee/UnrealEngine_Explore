// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu.h"
#include "UnrealEngine_ExploreGameModeBase.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void UStartMenu::NativeConstruct() {
	Super::NativeConstruct();

	FScriptDelegate StartGameButtonDelegte;
	StartGameButtonDelegte.BindUFunction(this, "StartGame");
	StartGameButton->OnClicked.Add(StartGameButtonDelegte);

	FScriptDelegate StartGameButtonHoveredDelegte;
	StartGameButtonHoveredDelegte.BindUFunction(this, "StartGameHovered");
	StartGameButton->OnHovered.Add(StartGameButtonHoveredDelegte);

	FScriptDelegate StartGameButtonUnoveredDelegte;
	StartGameButtonUnoveredDelegte.BindUFunction(this, "StartGameUnhovered");
	StartGameButton->OnUnhovered.Add(StartGameButtonUnoveredDelegte);

	FScriptDelegate QuitGameButtonDelegte;
	QuitGameButtonDelegte.BindUFunction(this, "QuitGame");
	QuitGameButton->OnClicked.Add(QuitGameButtonDelegte);

	FScriptDelegate QuitGameButtonHoveredDelegte;
	QuitGameButtonHoveredDelegte.BindUFunction(this, "QuitGameHovered");
	QuitGameButton->OnHovered.Add(QuitGameButtonHoveredDelegte);

	FScriptDelegate QuitGameButtonUnoveredDelegte;
	QuitGameButtonUnoveredDelegte.BindUFunction(this, "QuitGameUnhovered");
	QuitGameButton->OnUnhovered.Add(QuitGameButtonUnoveredDelegte);

	InputWarningText->SetVisibility(ESlateVisibility::Collapsed);
	WarningTextFadeTime = 1.0f;
	bWarningTextVis = false;

	bClickable = false;
}

void UStartMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (bWarningTextVis) {
		FLinearColor color = InputWarningText->ColorAndOpacity.GetSpecifiedColor();
		float opacity = color.A;
		opacity -= InDeltaTime / WarningTextFadeTime;
		if (opacity <= 0.0f) {
			InputWarningText->SetVisibility(ESlateVisibility::Collapsed);
			bWarningTextVis = false;
		}
		else {
			color.A = opacity;
			InputWarningText->ColorAndOpacity = FSlateColor(color);
		}
	}
}

void UStartMenu::StartGame() {
	if (bClickable) {
		FText InputText = InputTextBox->GetText();
		AUnrealEngine_ExploreGameModeBase* MyGameModeBase = Cast<AUnrealEngine_ExploreGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (MyGameModeBase) MyGameModeBase->StartGame(InputText);
	}
	else {
		InputWarningText->SetVisibility(ESlateVisibility::Visible);
		FLinearColor color = InputWarningText->ColorAndOpacity.GetSpecifiedColor();
		color.A = 1.0f;
		InputWarningText->ColorAndOpacity = FSlateColor(color);
		bWarningTextVis = true;
	}
}

void UStartMenu::StartGameHovered() {
	if (!InputTextBox->GetText().IsEmpty()) {
		bClickable = true;
		StartGameButton->SetBackgroundColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
	}
	else {
		bClickable = false;
		StartGameButton->SetBackgroundColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

void UStartMenu::StartGameUnhovered() {
	StartGameButton->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	bClickable = false;
}

void UStartMenu::QuitGame() {
	AUnrealEngine_ExploreGameModeBase* MyGameModeBase = Cast<AUnrealEngine_ExploreGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MyGameModeBase) MyGameModeBase->QuitGame();
}

void UStartMenu::QuitGameHovered() {
	QuitGameButton->SetBackgroundColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
}

void UStartMenu::QuitGameUnhovered() {
	QuitGameButton->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
}

