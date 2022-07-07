// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenu.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UNREALENGINE_EXPLORE_API UStartMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool bClickable;

	float WarningTextFadeTime;
	bool bWarningTextVis;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* MaterialTexture;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class USlider* RSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class USlider* GSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class USlider* BSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UEditableTextBox* InputTextBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* InputWarningText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* StartGameButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* QuitGameButton;

	UFUNCTION()
		void StartGame();

	UFUNCTION()
		void StartGameHovered();

	UFUNCTION()
		void StartGameUnhovered();

	UFUNCTION()
		void QuitGame();

	UFUNCTION()
		void QuitGameHovered();

	UFUNCTION()
		void QuitGameUnhovered();

	
};
