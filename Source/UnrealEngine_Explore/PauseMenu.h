// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UNREALENGINE_EXPLORE_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* PauseText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* RestartButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* ResumeButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* QuitButton;

	UFUNCTION()
		void RestartGame();

	UFUNCTION()
		void ResumeGame();

	UFUNCTION()
		void QuitGame();

	UFUNCTION()
		void OnHovered();

	UFUNCTION()
		void OnUnhovered();
};
