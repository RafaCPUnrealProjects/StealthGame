// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StealthExtractionZone.generated.h"

UCLASS()
class STEALTHGAME_API AStealthExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	AStealthExtractionZone();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UDecalComponent* DecalComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundBase* ObjectiveMissionSound;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
