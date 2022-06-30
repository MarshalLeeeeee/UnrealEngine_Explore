// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetForExplore.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UNREALENGINE_EXPLORE_API UUserWidgetForExplore : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* TestTitle;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* SecondTitle;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* RestartButton;

	UFUNCTION()
		void RestartGame();

public:
	void SetTestTitle(FText text);
	void SetLostPawnCnt(int cnt);
};
