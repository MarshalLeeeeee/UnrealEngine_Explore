// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetForExplore.h"
#include "Components/TextBlock.h"

void UUserWidgetForExplore::NativeConstruct() {
	Super::NativeConstruct();

	TestTitle->SetText(FText::FromString(TEXT("Hello world!")));
	SecondTitle->SetText(FText::FromString(FString::Printf(TEXT("Lost block: %d"),0)));
}

void UUserWidgetForExplore::SetTestTitle(FText text) {
	TestTitle->SetText(text);
}

void UUserWidgetForExplore::SetLostPawnCnt(int cnt) {
	SecondTitle->SetText(FText::FromString(FString::Printf(TEXT("Lost block: %d"), cnt)));
}