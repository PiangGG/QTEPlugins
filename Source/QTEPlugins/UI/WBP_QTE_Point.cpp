// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_QTE_Point.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "QTEPlugins/GameInstanceSubsystem_QTE.h"

bool UWBP_QTE_Point::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (PointButton)
	{
		PointButton->SetStyle(PointButtonStyle);
		
		if (GetWorld())
		{
			FScriptDelegate sgbDelegate;
			sgbDelegate.BindUFunction(GetWorld()->GetFirstPlayerController(), "PointButtonOnClick");
			PointButton->OnClicked.Add(sgbDelegate);
			//PointButton->OnClicked.AddDynamic(GetWorld()->GetFirstPlayerController(),&UWBP_QTE_Point::PointButtonOnClick);
		}
	}
	
	return true;
}

void UWBP_QTE_Point::Start(FStartQTEStruct const& Data)
{
	CurrentTime = Data.MaxTime;
	
	
	MaterialInterface = LoadObject<UMaterialInterface>(NULL,TEXT("Material'/QTEPlugins/Materials/M_CircularProgressBar.M_CircularProgressBar'"));
	if (MaterialInterface)
	{
		if (!MaterialInstanceDynamic)
		{
			MaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this,MaterialInterface);
		}
		
		if (MaterialInstanceDynamic)
		{
			MaterialInstanceDynamic->SetScalarParameterValue(FName("CDController"),CurrentTime);
			if (TimeLineImage)
			{
				
				TimeLineImage->SetBrushFromMaterial(MaterialInstanceDynamic);
			}
			
			GetWorld()->GetTimerManager().SetTimer(TH_CountDown,this,&UWBP_QTE_Point::UpdatePersent,0.001,true);
		}
	}
}

void UWBP_QTE_Point::End()
{
	UGameInstanceSubsystem_QTE *GameInstanceSubsystem_QTE = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UGameInstanceSubsystem_QTE>();
	if (GameInstanceSubsystem_QTE)
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_CountDown);
		GameInstanceSubsystem_QTE->End(true);
	}
}

void UWBP_QTE_Point::PointButtonOnClick()
{
	End();
}

void UWBP_QTE_Point::Init()
{
	UE_LOG(LogTemp,Warning,TEXT("Init"))
	if (PointButton)
	{
		/*FScriptDelegate sgbDelegate;
		sgbDelegate.BindUFunction(this, "PointButtonOnClick");
		PointButton->OnClicked.Add(sgbDelegate);*/
		PointButton->OnClicked.AddDynamic(this,&ThisClass::PointButtonOnClick);
	}
}

void UWBP_QTE_Point::UpdatePersent()
{
	CurrentTime = FMath::FInterpTo(CurrentTime,0,0.001f,InterpSpeed);
	
	//UE_LOG(LogTemp,Warning,TEXT("%f"),CurrentTime)
	MaterialInstanceDynamic->SetScalarParameterValue(FName("CDController"),CurrentTime);
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
