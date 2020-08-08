// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StealthObjectiveActor.generated.h"

UCLASS()
class STEALTHGAME_API AStealthObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStealthObjectiveActor();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffects();

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	class UParticleSystem* PickupFX;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
