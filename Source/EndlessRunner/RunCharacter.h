// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunCharacter.generated.h"

UCLASS()
class ENDLESSRUNNER_API ARunCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARunCharacter();
	UFUNCTION(BlueprintImplementableEvent, Category = "Lane")
	void ChangeLane();
	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneUpdate( const float Value);
	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneFinished();
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	int32 CurrentLane = 0;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	int32 NextLane = 1;
	UFUNCTION(BlueprintCallable)
    void Death();
	UFUNCTION()
	void ResetLevel();
	UPROPERTY(EditAnywhere, Category = "Effects");
	class UParticleSystem* DeathEffect;
	UPROPERTY(EditAnywhere, Category = "Effects");
	class USoundBase* DeathSound;
	UFUNCTION()
	void AddCoin();
	UFUNCTION()
	void AutoRuning();
		// UPROPERTY(EditAnywhere)
		// float Speed = 100.f;
		// UPROPERTY(EditAnywhere)
		// float MaxSpeed = 80000;
		// UFUNCTION(BlueprintCallable)
		// void SetSpeed();
protected:

    UFUNCTION(BlueprintCallable)
    void OnDeath();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
	class USpringArmComponent* CameraArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
	class UCameraComponent*  Camera;
	UFUNCTION()
	void MoveRight();
	UFUNCTION()
	void MoveLeft();
	UFUNCTION()
	void MoveDown();
	UPROPERTY(VisibleInstanceOnly)
	class AEndlessRunnerGameModeBase* RunGameMode;
	UPROPERTY(EditAnywhere)
	FTimerHandle RestartTimeHandle; 
	UPROPERTY()
	class APlayerStart* PlayerStart;
	bool bIsAlive = true;

 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
