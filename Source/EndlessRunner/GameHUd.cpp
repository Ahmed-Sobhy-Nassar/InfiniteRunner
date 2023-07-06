// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUd.h"
#include "EndlessRunnerGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"   

void UGameHUd::InitializeHud(AEndlessRunnerGameModeBase* RunGameMode)
{
     if(RunGameMode)
     {
        CoinCounter->SetText(FText::AsNumber(0));
        LivesCounter->SetText(FText::AsNumber(RunGameMode->MaxLives));
         RunGameMode->OnCoinCounterChange.AddDynamic(this, &UGameHUd::SetCoinCount);
         RunGameMode->OnivesCounterChange.AddDynamic(this, &UGameHUd::SetLivesCount);

     }
}

void UGameHUd:: SetCoinCount(const int32 count)
{
 CoinCounter->SetText(FText::AsNumber(count));
}

void UGameHUd::SetLivesCount(const int32 count)
{
   LivesCounter->SetText(FText::AsNumber(count));
}

void UGameHUd::NativeConstruct()
{
   if(PauseBtn)
   {
      PauseBtn->OnClicked.AddDynamic(this, &UGameHUd::OnPauseClick);
   }
   UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this); 
}

void UGameHUd::OnPauseClick()
 {
    if(!PauseMenuWidgetClass) return;  
   UGameplayStatics::SetGamePaused(GetWorld(), true);
   UUserWidget* Widget = CreateWidget(GetWorld(), PauseMenuWidgetClass);
   if(Widget)
   {
      Widget->AddToViewport();
   }
}