// Fill out your copyright notice in the Description page of Project Settings.
#include "CoinItem.h"
#include "RunCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"


// Sets default values
ACoinItem::ACoinItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	SphereColider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereColider"));
	SphereColider->SetupAttachment(SceneComponent);
	SphereColider->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	MeshComponent->SetupAttachment(SphereColider);
	MeshComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationMovement"));
	RotatingMovement->RotationRate = FRotator (0, 180, 0); 



}

// Called when the game starts or when spawned
void ACoinItem::BeginPlay()
{
	Super::BeginPlay();
	SphereColider->OnComponentBeginOverlap.AddDynamic(this, &ACoinItem::OnSphereOverlap);
	
}
void ACoinItem::OnSphereOverlap(UPrimitiveComponent* OverlapComponent, AActor* OthereActor, UPrimitiveComponent* OthereComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ARunCharacter* RunCharacter = Cast<ARunCharacter>(OthereActor);
	if(RunCharacter)
	{  
		if(CoinSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), CoinSound, GetActorLocation());
		}
		RunCharacter->AddCoin();
		Destroy();
	}
}
