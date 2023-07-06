// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinItem.generated.h"
UCLASS()
class ENDLESSRUNNER_API ACoinItem : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ACoinItem();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereColider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class URotatingMovementComponent* RotatingMovement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	class USoundBase* CoinSound;
    UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlapComponent, AActor* OthereActor, UPrimitiveComponent* OthereComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
