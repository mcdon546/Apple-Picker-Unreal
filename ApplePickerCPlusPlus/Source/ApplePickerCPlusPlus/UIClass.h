// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIClass.generated.h"

/**
 * 
 */
UCLASS()
class APPLEPICKERCPLUSPLUS_API UUIClass : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) class UTextBlock* ScoreText;

public:
	void SetScoreDisplay(FString score);
};
