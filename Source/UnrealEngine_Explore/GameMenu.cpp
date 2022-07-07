// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenu.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameMenu::NativeConstruct() {
	Super::NativeConstruct();

	TestTitle->SetText(FText::FromString(TEXT("Player name: ")));
	SecondTitle->SetText(FText::FromString(FString::Printf(TEXT("Lost block: %d"), 0)));
}

void UGameMenu::SetTestTitle(FText text) {
	FString str = FString("Player name: ") + text.ToString();
	TestTitle->SetText(FText::FromString(str));
}

void UGameMenu::SetLostPawnCnt(int cnt) {
	SecondTitle->SetText(FText::FromString(FString::Printf(TEXT("Lost block: %d"), cnt)));
}