// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ArrowComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

class UArrowComponent;

UCLASS()
class ENDLESSRUNNER_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorTile();
	  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coins")
	  TSubclassOf<class ACoinItem> CoinClass;
      UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstecals")
	  TSubclassOf<class AObstical> ObsticalClass;
	  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstecals")
	  TSubclassOf<class AObstical> BigObsticalClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* RightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* LeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* FloorTriggerBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> ChildActors; // to add and copy the obstecals and coins when floor tiles are destored
	
	FORCEINLINE const FTransform GetAttachTransform() const
	{
		return AttachPoint->GetComponentTransform();
	}
	UFUNCTION()
	void SpwanItem();
	UFUNCTION()
	void DestroyFloorTile();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configration")
	float SpawnPercent1 = .1f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configration")
	float SpawnPercent2 = .3f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configration")
	float SpawnPercent3 = .5f;
	UPROPERTY()
	int32 Prevent = 0;
	UPROPERTY()
	int32 PreventCoines = 0;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    UPROPERTY(VisibleInstanceOnly)
	class AEndlessRunnerGameModeBase* RunGameMode;
	UPROPERTY()
	FTimerHandle DestroyHandle;
	UFUNCTION()
	void SpawnLaneItem(UArrowComponent* Lane, int32 PreventThreeBigObstecal, int32 coinsRepetion);
	UFUNCTION()
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyEndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
