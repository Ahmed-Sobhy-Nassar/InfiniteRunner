// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "EndlessRunnerGameModeBase.h"



// Sets default values
ARunCharacter::ARunCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->TargetArmLength = 350.f;
	CameraArm->SocketOffset = FVector(0.f, 0.f, 100.f);
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);


}

// Called when the game starts or when spawned
void ARunCharacter::BeginPlay()
{
	Super::BeginPlay();
	RunGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	check(RunGameMode);
	RunGameMode->OnLevelRestet.AddDynamic(this, &ARunCharacter::ResetLevel);
	PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));

	
}

// Called every frame
void ARunCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AutoRuning();
	

}
void ARunCharacter::ChangeLaneUpdate(const float Value)
{
    FVector Location = GetCapsuleComponent()->GetComponentLocation();
	Location.Y = FMath::Lerp(RunGameMode->LaneSwitchValue[CurrentLane], RunGameMode->LaneSwitchValue[NextLane], Value);
	SetActorLocation(Location);
}

void ARunCharacter:: ChangeLaneFinished()
{
       CurrentLane = NextLane;
}
// Called to bind functionality to input
void ARunCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARunCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ARunCharacter::StopJumping);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ARunCharacter::MoveRight);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ARunCharacter::MoveLeft);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &ARunCharacter::MoveDown);

}

void ARunCharacter::MoveLeft()
{
     NextLane = FMath::Clamp(CurrentLane -1, 0 , 2);
	 ChangeLane();
}

void ARunCharacter:: MoveRight()
{
	NextLane = FMath::Clamp(CurrentLane +1, 0 , 2);
	ChangeLane();
}

void ARunCharacter:: MoveDown()
{
	static FVector Impulse = FVector(0.f, 0.f, 1000.f);
      // GetCharacterMovement()->AddImpulse(Impulse, true);
	  // there is an error C2077
	
}

void ARunCharacter::Death()
{

	if(bIsAlive){
		const FVector Location = GetActorLocation();
		UWorld* World = GetWorld();
		if(World)
		{
			bIsAlive = false;
			DisableInput(nullptr);

	        if(DeathEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(World, DeathEffect, Location);
			}
			if(DeathSound)
			{
				UGameplayStatics::PlaySoundAtLocation(World, DeathSound, Location);
			}
		}
		GetMesh()->SetVisibility(false);
		World->GetTimerManager().SetTimer(RestartTimeHandle, this, &ARunCharacter::OnDeath, 2.f);
	}
}

void ARunCharacter::OnDeath()
{      
	bIsAlive = true;
    if(RestartTimeHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(RestartTimeHandle);
	}
	RunGameMode->PlayerDied();
   // UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
}

void ARunCharacter::ResetLevel()
{
     bIsAlive = true;
	 EnableInput(nullptr);
	 GetMesh()->SetVisibility(true);
	 if(PlayerStart)
	 {
		 SetActorLocation(PlayerStart->GetActorLocation());
		 SetActorRotation(PlayerStart->GetActorRotation());
	 }

}

void ARunCharacter:: AddCoin()
{
	RunGameMode->AddCoin();
}
void ARunCharacter:: AutoRuning()
{   
	
	FRotator ContorlRotation = GetControlRotation();
	ContorlRotation.Roll = 0.f;
	ContorlRotation.Pitch = 0.f;
    AddMovementInput(ContorlRotation.Vector());
}
// void ARunCharacter::SetSpeed()
// {     
// 	In the future inSha'Allah
// }