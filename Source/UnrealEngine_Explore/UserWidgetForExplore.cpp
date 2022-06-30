// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetForExplore.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUserWidgetForExplore::NativeConstruct() {
	Super::NativeConstruct();

	TestTitle->SetText(FText::FromString(TEXT("Hello world!")));
	SecondTitle->SetText(FText::FromString(FString::Printf(TEXT("Lost block: %d"),0)));

	FScriptDelegate RestartButtonDelegte;
	RestartButtonDelegte.BindUFunction(this, "RestartGame");
	RestartButton->OnClicked.Add(RestartButtonDelegte);
}

void UUserWidgetForExplore::SetTestTitle(FText text) {
	TestTitle->SetText(text);
}

void UUserWidgetForExplore::SetLostPawnCnt(int cnt) {
	SecondTitle->SetText(FText::FromString(FString::Printf(TEXT("Lost block: %d"), cnt)));
}

void UUserWidgetForExplore::RestartGame() {
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}