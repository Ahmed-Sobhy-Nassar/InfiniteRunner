// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstical.h"
#include "Components/SceneComponent.h"
#include "RunCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AObstical::AObstical()
{
 	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneComponent);
    StaticMesh->OnComponentHit.AddDynamic(this, &AObstical::OnObstecalHit);
}

void AObstical::OnObstecalHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ARunCharacter* RunCharacter = Cast<ARunCharacter>(OtherActor);
	if(RunCharacter)
	{
		RunCharacter->Death();
	}

}

