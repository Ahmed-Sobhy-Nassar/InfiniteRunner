// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"   
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
void UPauseMenu::NativeConstruct()
{
   if(ContinueBtn)
   {
      ContinueBtn->OnClicked.AddDynamic(this, &UPauseMenu::OnContinueClick);
   }
   if(RestrartBtn)
   {
       RestrartBtn->OnClicked.AddDynamic(this, &UPauseMenu::OnRestartClick);
   }
}
void UPauseMenu::OnContinueClick()
{
    UGameplayStatics::SetGamePaused(GetWorld(), false);
    RemoveFromParent();
}
void UPauseMenu::OnRestartClick()
{ 
    UWorld* World =GetWorld();
    if(World)
    {
         UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
    }
}


