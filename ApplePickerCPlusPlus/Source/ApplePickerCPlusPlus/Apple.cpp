// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"
#include "Baskets.h"

// Sets default values
AApple::AApple()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GCollider"));
	RootComponent = Collider;
}

// Called when the game starts or when spawned
void AApple::BeginPlay()
{
	Super::BeginPlay();
	
	// Register hit function
	Collider->OnComponentHit.AddDynamic(this, &AApple::OnHit);
}

// Called every frame
void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Remove a basket if below min height
	if (GetActorLocation().Z < MinHeight)
	{
		UE_LOGFMT(LogTemp, Log, "Dropped below min height");

		ABaskets* Baskets = Cast<ABaskets>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		Baskets->RemoveBasket();

		Destroy();
	}
}

void AApple::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector normalImpulse, const FHitResult& Hit)
{
	//Check if hit the baskets
	if (ABaskets* Baskets = Cast<ABaskets>(OtherActor))
	{
		Baskets->AddScore(ScoreValue);

		Destroy(); //Destroy this apple
	}

}

