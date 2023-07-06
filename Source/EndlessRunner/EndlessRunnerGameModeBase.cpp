// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameModeBase.h"
#include "FloorTile.h"
#include "GameHUd.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AEndlessRunnerGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    NumberOfLives = MaxLives;
    CreateInitialFloorTiles();
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
    GameHud = Cast<UGameHUd>(CreateWidget(GetWorld(), GameHUDClass));
    check(GameHud);
    GameHud->InitializeHud(this);
    GameHud->AddToViewport();

}

void AEndlessRunnerGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEndlessRunnerGameModeBase::CreateInitialFloorTiles()
{ 
    AFloorTile* Tile = AddFloorTiles(false);
    if(Tile)
    {
        LaneSwitchValue.Add(Tile->LeftLane->GetComponentLocation().Y);
        LaneSwitchValue.Add(Tile->CenterLane->GetComponentLocation().Y);
        LaneSwitchValue.Add(Tile->RightLane->GetComponentLocation().Y);
    }
    for(int i = 0; i < NumInitialFloorTiles; ++i)
    {
              AddFloorTiles(true);
    }
}

AFloorTile* AEndlessRunnerGameModeBase::AddFloorTiles(const bool bSpawnItem)
{

    UWorld* World =  GetWorld();
    if(World)
    {
        AFloorTile* Tile = World->SpawnActor<AFloorTile>(FloorTileClass, NextSpawnPoint);
        if(Tile)
        { 
             FloorTilesArray.Add(Tile);
            if(bSpawnItem)
            {
                Tile->SpwanItem();
            }
            NextSpawnPoint = Tile->GetAttachTransform();
        }
         return Tile;
    }
    return nullptr;
}
void AEndlessRunnerGameModeBase:: AddCoin()
{
    TotalCoins ++;
    
     OnCoinCounterChange.Broadcast(TotalCoins);
}

void AEndlessRunnerGameModeBase::RemoveTiles(AFloorTile* Tile)
{
     FloorTilesArray.Remove(Tile);
}
void AEndlessRunnerGameModeBase::PlayerDied()
{
    NumberOfLives--;
    OnivesCounterChange.Broadcast(NumberOfLives);
    if(NumberOfLives > 0)
    {   //Iterate all FloorTiles and call DestroyFloorTile();
        for(AFloorTile* Tile : FloorTilesArray)
        {
            Tile->DestroyFloorTile(); 
        } 
        // Empty the Array
        FloorTilesArray.Empty();
        // Set the next spawn point to  initail value
        NextSpawnPoint =  FTransform();
        // CreateInitialFloorTiles();
        CreateInitialFloorTiles();
        // BroadCast level restart event 
        OnLevelRestet.Broadcast(); 
    }
    else 
    {
        // GameOver();
    }

}