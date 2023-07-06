// Fill out your copyright notice in the Description page of Project Settings.
#include "FloorTile.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CoinItem.h"
#include "Components/ArrowComponent.h"
#include "Components/PrimitiveComponent.h"
#include "EndlessRunnerGameModeBase.h"
#include "Components/BoxComponent.h"
#include "RunCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Obstical.h"

// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent> (TEXT("FloorMesh"));
    FloorMesh->SetupAttachment(SceneComponent);

	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachPoint"));
	AttachPoint->SetupAttachment(SceneComponent);

	CenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("CenterLane"));
	CenterLane->SetupAttachment(SceneComponent);

	RightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("RightLane"));
	RightLane->SetupAttachment(SceneComponent);

	LeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftLane"));
	LeftLane->SetupAttachment(SceneComponent);

	FloorTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorTriggerBox"));
	FloorTriggerBox->SetupAttachment(SceneComponent);
	FloorTriggerBox->SetBoxExtent(FVector(32.f, 500.f, 200.f));
    FloorTriggerBox->SetCollisionProfileName(TEXT("OverLapOnlyPawn"));
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();
	RunGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	check(RunGameMode);
	FloorTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnTriggerBoxOverlap);
}

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}  
// OnTriggerBoxOverlap for adding a new tile by calling AddFloorTiles from the game mode when the player reach the the end of the tile befor it and destroy the last tile 
void AFloorTile::OnTriggerBoxOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyEndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunCharacter* RunCharacter = Cast<ARunCharacter>(OtherActor);
	if(RunCharacter)
	{
		 RunGameMode->AddFloorTiles(true);
		GetWorldTimerManager().SetTimer(DestroyHandle, this, &AFloorTile::DestroyFloorTile, 2.f, false );
	}
}

void AFloorTile:: DestroyFloorTile(){
   if(DestroyHandle.IsValid())
   {   // clear the time 
	   GetWorldTimerManager().ClearTimer(DestroyHandle);

   } 
    for(AActor* Child : ChildActors) // Desroty The Obstecals and coins befor calling GameMode
	{
		if(Child)
		{
			Child->Destroy();
		}
	}
	ChildActors.Empty(); // empty the array  before removing the tile 
   // remove the tile from the array 
   RunGameMode->RemoveTiles(this);
   this->Destroy();
}
 // spawn obstecals and coins on the tiles 
void AFloorTile::SpwanItem()
{
	if(ObsticalClass != nullptr && BigObsticalClass != nullptr && CoinClass != nullptr)
	{
		SpawnLaneItem(CenterLane, Prevent,PreventCoines);
		SpawnLaneItem(RightLane, Prevent,PreventCoines);
		SpawnLaneItem(LeftLane, Prevent,PreventCoines);
	}
	 
} 
// spawn items on the tiles 
void AFloorTile:: SpawnLaneItem(UArrowComponent* Lane, int32 PreventThreeBigObstecal , int32 coinsRepetion)
{ 
	const float RandValue = FMath::FRandRange(0.f, 1.f); 
	FActorSpawnParameters SpawnParameters;
    
	const FTransform& SpawnLocation = Lane->GetComponentTransform();
	 
	if(UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent1, SpawnPercent2, true, true))
	{
		AObstical* Obstecal = GetWorld()->SpawnActor<AObstical>(ObsticalClass, SpawnLocation, SpawnParameters);
		ChildActors.Add(Obstecal);
	}
	else if(UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent2, SpawnPercent3, true, true))
	{
		if(PreventThreeBigObstecal < 2)
		{
        	AObstical* Obstecal = GetWorld()->SpawnActor<AObstical>(BigObsticalClass, SpawnLocation, SpawnParameters);
			
			if(Obstecal)
			{
				PreventThreeBigObstecal++;
				Prevent = PreventThreeBigObstecal;
			}
			ChildActors.Add(Obstecal);
		}
		else
		{
			AObstical* Obstecal = GetWorld()->SpawnActor<AObstical>(ObsticalClass, SpawnLocation, SpawnParameters);
			ChildActors.Add(Obstecal);
		}

	}
	else if(UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent3, 1.f, true, true))
	{   
		if(coinsRepetion < 1)
		{
			ACoinItem* Coin = GetWorld()->SpawnActor<ACoinItem>(CoinClass, SpawnLocation, SpawnParameters);
			ChildActors.Add(Coin);
            coinsRepetion ++;
			PreventCoines = coinsRepetion;
		}
		else 
		{
			AObstical* Obstecal = GetWorld()->SpawnActor<AObstical>(ObsticalClass, SpawnLocation, SpawnParameters);
			ChildActors.Add(Obstecal);
		}
	}
}