// Fill out your copyright notice in the Description page of Project Settings.


#include "Baskets.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"
#include "Blueprint/UserWidget.h"
#include "UIClass.h"

// Sets default values
ABaskets::ABaskets()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize scene root
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("GSceneRoot"));
	SetRootComponent(SceneComponent);

	// Initialize basket meshes
	for (int i = 0; i < BasketCount; i++)
	{
		UStaticMeshComponent* CreatedBasket = CreateDefaultSubobject<UStaticMeshComponent>(FName("GBasket_" + FString::FromInt(i)));
		CreatedBasket->SetupAttachment(SceneComponent);
		CreatedBasket->RegisterComponent();
		BasketMeshes.Add(CreatedBasket);
	}
}

// Called when the game starts or when spawned
void ABaskets::BeginPlay()
{
	Super::BeginPlay();
	
	DistanceFromCamera = FVector::Distance(GetActorLocation(), CameraActor->GetActorLocation());

	UI = Cast<UUIClass>(CreateWidget(GetWorld(), UIBP));
	UI->AddToViewport();
}

// Called every frame
void ABaskets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move based on mouse position
	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

	SetActorLocation(FVector(GetActorLocation().X, (MouseWorldLocation + MouseWorldDirection * DistanceFromCamera).Y, GetActorLocation().Z));
}

// Called to bind functionality to input
void ABaskets::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called to add to the player's score
void ABaskets::AddScore(int ScoreChange)
{
	Score += ScoreChange;
	UI->SetScoreDisplay(FString::FromInt(Score));
}

// Called to remove one of the baskets
void ABaskets::RemoveBasket()
{
	UE_LOGFMT(LogTemp, Log, "Removing a basket");

	BasketCount--;
	BasketMeshes[BasketCount]->DestroyComponent();
	BasketMeshes.RemoveAt(BasketCount);

	// Restart game if no baskets remaining
	if (BasketCount == 0)
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}

