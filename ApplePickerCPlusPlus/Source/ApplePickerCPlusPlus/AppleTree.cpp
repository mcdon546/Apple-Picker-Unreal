// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleTree.h"
#include "Logging/StructuredLog.h"

// Sets default values
AAppleTree::AAppleTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAppleTree::BeginPlay()
{
	Super::BeginPlay();
	
	// Save start position
	StartPosition = GetActorLocation();

	GetWorldTimerManager().SetTimer(DropAppleTimer, this, &AAppleTree::DropApple, AppleSpawnDelay, true, AppleSpawnDelay);
}

// Called every frame
void AAppleTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move
	SetActorLocation(GetActorLocation() + FVector(0, 1, 0) * MoveSpeed * MoveDirection * DeltaTime);

	// Switch direction when reaching the edge
	if (FVector::Distance(GetActorLocation(), StartPosition) > MoveDistance)
	{
		MoveDirection *= -1;
	}
	// Switch direction randomly
	else if (FMath::RandRange(0.0, 1.0) < ChangeDirectionChance)
	{
		MoveDirection *= -1;
	}
}

void AAppleTree::DropApple()
{
	UE_LOGFMT(LogTemp, Log, "Dropping Apple");

	GetWorld()->SpawnActor<AApple>(AppleBP, GetActorLocation(), FRotator());
}

