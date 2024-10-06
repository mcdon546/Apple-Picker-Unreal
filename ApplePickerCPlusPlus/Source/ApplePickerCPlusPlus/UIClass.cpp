// Fill out your copyright notice in the Description page of Project Settings.


#include "UIClass.h"
#include "Components/TextBlock.h"

void UUIClass::SetScoreDisplay(FString Score)
{
	ScoreText->SetText(FText::FromString(Score));
}
