// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Apple.h"
#include "AppleTree.generated.h"

UCLASS()
class APPLEPICKERCPLUSPLUS_API AAppleTree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAppleTree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere); float MoveDistance;
	UPROPERTY(EditAnywhere); float MoveSpeed;
	UPROPERTY(EditAnywhere); float ChangeDirectionChance;
	UPROPERTY(EditAnywhere); float AppleSpawnDelay;
	UPROPERTY(EditAnywhere); TSubclassOf<AApple> AppleBP;

	FVector StartPosition;
	float MoveDirection = 1;
	FTimerHandle DropAppleTimer;

private:
	void DropApple();
};
