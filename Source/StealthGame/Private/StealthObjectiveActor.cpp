// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/StealthObjectiveActor.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include "StealthGameCharacter.h"

// Sets default values
AStealthObjectiveActor::AStealthObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AStealthObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	
	PlayEffects();
}

void AStealthObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

// Called every frame
// void AStealthObjectiveActor::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// 
// }

void AStealthObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	AStealthGameCharacter* MyCharacter = Cast<AStealthGameCharacter>(OtherActor);
	if(MyCharacter)
	{
		MyCharacter->bIsCarryingObjective = true;

		Destroy();
	}
}

