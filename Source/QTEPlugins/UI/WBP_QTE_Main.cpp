// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_QTE_Main.h"

#include "WBP_QTE_Line.h"
#include "WBP_QTE_Point.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/NamedSlot.h"
#include "Kismet/GameplayStatics.h"
#include "QTEPlugins/GameInstanceSubsystem_QTE.h"

void UWBP_QTE_Main::Start(FStartQTEStruct const &Data )
{
	GameInstanceSubsystem_QTE = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UGameInstanceSubsystem_QTE>();
	
	if (CanvasPanel)
	{
		
		CanvasPanel->AddChildToCanvas(NamedSlot);
	}
	if (NamedSlot)
	{
		//设置位置
		CastChecked<UCanvasPanelSlot>(NamedSlot->Slot)->SetPosition(Data.Location);
		//设置角度
		NamedSlot->SetRenderTransformAngle(Data.Angle);
		
		if (!GameInstanceSubsystem_QTE)return;
		
		switch (Data.Type)
		{
		case EStartQTEType::Point:
			if (!GameInstanceSubsystem_QTE->QTEWidet_Point)return;

			GameInstanceSubsystem_QTE->QTE_Point = CreateWidget<UWBP_QTE_Point>(this,GameInstanceSubsystem_QTE->QTEWidet_Point);
			NamedSlot->AddChild(CastChecked<UWBP_QTE_Point>(GameInstanceSubsystem_QTE->QTE_Point));
			GameInstanceSubsystem_QTE->QTE_Point->Initialize();
			GameInstanceSubsystem_QTE->QTE_Point->Start(Data);
			break;
		case EStartQTEType::Line:
			if (!GameInstanceSubsystem_QTE->QTEWidet_Line)return;

			GameInstanceSubsystem_QTE->QTE_Line = CreateWidget<UWBP_QTE_Line>(this,GameInstanceSubsystem_QTE->QTEWidet_Line);
			NamedSlot->AddChild(CastChecked<UWBP_QTE_Line>(GameInstanceSubsystem_QTE->QTE_Line));
			GameInstanceSubsystem_QTE->QTE_Line->Initialize();
			GameInstanceSubsystem_QTE->QTE_Line->Start(Data);
			break;
		case EStartQTEType::Ring:
			
			break;
		default:

			break;
		}
	}
	
	AddToViewport();
}

void UWBP_QTE_Main::End(bool bSuccess)
{
	if (bSuccess)
	{
		auto FoundFunc = this->FindFunction(FName("Success"));
		if (FoundFunc && (FoundFunc->ParmsSize == 0))
		{
			ProcessEvent(FoundFunc, nullptr);
		}
		//SuccessEvent();
	}
	else
	{
		auto FoundFunc = this->FindFunction(FName("Fail"));
		if (FoundFunc && (FoundFunc->ParmsSize == 0))
		{
			ProcessEvent(FoundFunc, nullptr);
		}
		//FailEvent();
	}
	if (GameInstanceSubsystem_QTE->QTE_Point)
	{
		GameInstanceSubsystem_QTE->QTE_Point->RemoveFromParent();
		GameInstanceSubsystem_QTE->QTE_Point = nullptr;
	}

	if (GameInstanceSubsystem_QTE->QTE_Line)
	{
		GameInstanceSubsystem_QTE->QTE_Line->RemoveFromParent();
		GameInstanceSubsystem_QTE->QTE_Line = nullptr;
	}
	
	RemoveFromParent();
}
