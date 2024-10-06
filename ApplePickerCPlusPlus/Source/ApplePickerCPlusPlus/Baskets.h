// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Baskets.generated.h"

UCLASS()
class APPLEPICKERCPLUSPLUS_API ABaskets : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaskets();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddScore(int scoreChange);
	void RemoveBasket();

	UPROPERTY(EditAnywhere) AActor* CameraActor;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> UIBP;
	
	UPROPERTY(EditAnywhere) TArray<UStaticMeshComponent*> BasketMeshes;
	
	float DistanceFromCamera;
	int Score = 0;
	int BasketCount = 3;
	class UUIClass* UI;

};
