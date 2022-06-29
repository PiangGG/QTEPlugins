// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_QTE_Line.h"

#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"
#include "QTEPlugins/GameInstanceSubsystem_QTE.h"

bool UWBP_QTE_Line::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (Sliderbar)
	{
		Sliderbar->WidgetStyle = SliderStyle;
	}
	if (ProgressBar)
	{
		ProgressBar->WidgetStyle = ProgressBarStyle;
	}
	
	return true;
}

void UWBP_QTE_Line::Start(FStartQTEStruct const& Data)
{
	MaxTime= Data.MaxTime;
	CurrentTime = Data.MaxTime;
	
	
	GetWorld()->GetTimerManager().SetTimer(TH_CountDown,this,&UWBP_QTE_Line::UpdatePersent,0.001,true);
}

void UWBP_QTE_Line::End()
{
	UGameInstanceSubsystem_QTE *GameInstanceSubsystem_QTE = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UGameInstanceSubsystem_QTE>();
	if (GameInstanceSubsystem_QTE)
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_CountDown);
		GameInstanceSubsystem_QTE->End(true);
	}
}

void UWBP_QTE_Line::Init()
{
	
}

void UWBP_QTE_Line::UpdatePersent()
{
	CurrentTime = FMath::FInterpTo(CurrentTime,0,0.001f,InterpSpeed);
	
	ProgressBar->SetPercent(CurrentTime/MaxTime);
	
	if (FMath::IsNearlyEqual(CurrentTime,0.0,0.1))
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_CountDown);
		UGameInstanceSubsystem_QTE *GameInstanceSubsystem_QTE = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UGameInstanceSubsystem_QTE>();
		if (GameInstanceSubsystem_QTE)
		{
			GameInstanceSubsystem_QTE->End(false);
		}
	}
}
