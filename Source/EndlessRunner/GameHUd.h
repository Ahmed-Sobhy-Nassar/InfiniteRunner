// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUd.generated.h"

UCLASS()
class ENDLESSRUNNER_API UGameHUd : public UUserWidget
{
	GENERATED_BODY()
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CoinCounter;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LivesCounter;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* PauseBtn;
	UFUNCTION()
	void OnPauseClick();
	UFUNCTION()
	virtual void NativeConstruct() override;
	public:	
	UFUNCTION(BlueprintCallable)
	void InitializeHud(class AEndlessRunnerGameModeBase* RunGameMode);
	UFUNCTION(BlueprintCallable)
	void SetCoinCount(const int32 count);
	UFUNCTION(BlueprintCallable)
	void SetLivesCount(const int32 count);
};
