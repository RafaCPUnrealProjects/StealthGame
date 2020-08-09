// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/StealthExtractionZone.h"
#include <Components/BoxComponent.h>
#include <Components/DecalComponent.h>
#include "StealthGameCharacter.h"
#include "StealthGameGameMode.h"
#include <Kismet/GameplayStatics.h>

AStealthExtractionZone::AStealthExtractionZone()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	
	RootComponent = OverlapComp;
	
	OverlapComp->SetHiddenInGame(false);
	
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AStealthExtractionZone::HandleOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200);
	DecalComp->SetupAttachment(RootComponent);
}

void AStealthExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AStealthGameCharacter* MyPawn = Cast<AStealthGameCharacter>(OtherActor);
	if(MyPawn && MyPawn->bIsCarryingObjective)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ObjectiveMissionSound, GetActorLocation());
		AStealthGameGameMode* GM = Cast<AStealthGameGameMode>(GetWorld()->GetAuthGameMode());
		if(GM)
		{
			GM->CompleteMission(MyPawn);
		}
	}
}
