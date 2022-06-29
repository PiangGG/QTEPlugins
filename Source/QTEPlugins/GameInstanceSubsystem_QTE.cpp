// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceSubsystem_QTE.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WBP_QTE_Point.h"

UGameInstanceSubsystem_QTE::UGameInstanceSubsystem_QTE()
{
	/*if (!PlayerController)
	{
		PlayerController = UGameplayStatics::GetPlayerController(GWorld,0);
	}
	QTEMain = CreateWidget<UWBP_QTE_Main>(PlayerController,QTEWidet);
	FString WidgetPath = FPaths::ProjectPluginsDir();*/

	
	static ConstructorHelpers::FClassFinder<UWBP_QTE_Main>WBP_QTE_Main(TEXT("Blueprint'/QTEPlugins/UI/WBP_QTE_Main_BP.WBP_QTE_Main_BP_C'")) ;
	QTEWidet = WBP_QTE_Main.Class;

	static ConstructorHelpers::FClassFinder<UWBP_QTE_Point>WBP_QTE_Point(TEXT("Blueprint'/QTEPlugins/UI/WBP_QTE_Point_BP.WBP_QTE_Point_BP_C'")) ;
	QTEWidet_Point = WBP_QTE_Point.Class;
	
	static ConstructorHelpers::FClassFinder<UWBP_QTE_Line>WBP_QTE_Line(TEXT("Blueprint'/QTEPlugins/UI/WBP_QTE_Line_BP.WBP_QTE_Line_BP_C'")) ;
	QTEWidet_Line = WBP_QTE_Line.Class;
}

void UGameInstanceSubsystem_QTE::Start(FStartQTEStruct const &Data )//:Data()= FStartQTEStruct(FVector2D(0.0f,0.0f),0.0f,2.0f,EStartQTEType::Point)
{
	/*if (GEngine)
	{
		FString WidgetPath = FPaths::ProjectPluginsDir();
		UE_LOG(LogTemp, Error, TEXT("Paths:%s!"),*WidgetPath);
	}*/
	
	if (bStartQTEing)return;
	bStartQTEing = true;
	
	if (QTEMain)
	{
		QTEMain->Start(Data);
	}
	else
	{
		QTEMain = CreateWidget<UWBP_QTE_Main>(GetWorld()->GetFirstPlayerController(), QTEWidet);
		if (QTEMain)
		{
			QTEMain->Start(Data);
		}
	}
	
}

void UGameInstanceSubsystem_QTE::End(bool bSuccess)
{
	if (bSuccess)
	{
		UE_LOG(LogTemp,Warning,TEXT("PointButtonOnClick:true"))
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("PointButtonOnClick:false"))
	}
	
	
	if (!bStartQTEing)return;
	bStartQTEing = false;
	
	if (QTEWidet)
	{
		QTEMain->End(bSuccess);
	}
}
