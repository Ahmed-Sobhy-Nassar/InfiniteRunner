// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.generated.h"

class AFloorTile;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinCounterChange, int32, CoinCounter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesCounterChange, int32, LivesCounter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelReset);
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:
	    UPROPERTY(EditAnywhere, Category = "Configration")	
		int32 NumInitialFloorTiles = 10;
		UPROPERTY(VisibleInstanceOnly, Category = "RunTime")
		FTransform NextSpawnPoint;
		UPROPERTY(EditAnywhere, Category = "Configration")
		TSubclassOf <AFloorTile> FloorTileClass;
		UPROPERTY(EditAnywhere, Category = "Configration")
		TSubclassOf <class UUserWidget> GameHUDClass;
		UPROPERTY(VisibleInstanceOnly, Category = "RunTime")
		class UGameHUd* GameHud;
		UFUNCTION(BlueprintCallable)
		void CreateInitialFloorTiles();
		UFUNCTION(BlueprintCallable)
		AFloorTile* AddFloorTiles(const bool bSpawnItem);
		UPROPERTY(EditAnywhere, Category = "Configration")
		TArray<float> LaneSwitchValue;
		UPROPERTY(EditAnywhere, Category = "Configration")
		TArray<AFloorTile*> FloorTilesArray;
		UFUNCTION(BlueprintCallable)
		void AddCoin();
		UFUNCTION(BlueprintCallable)
		void PlayerDied();
		UFUNCTION(BlueprintCallable)
		void RemoveTiles(AFloorTile* Tile);
		UPROPERTY(VisibleAnywhere)
		int32 TotalCoins = 0;
		UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
		FOnCoinCounterChange OnCoinCounterChange;
		UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
		FOnLivesCounterChange OnivesCounterChange;
		UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
		FOnLevelReset OnLevelRestet;
		UPROPERTY(VisibleAnywhere)
		int32 NumberOfLives = 0;
		UPROPERTY(EditAnywhere)
		int32 MaxLives = 3;
	protected:
		virtual void BeginPlay() override;
	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
