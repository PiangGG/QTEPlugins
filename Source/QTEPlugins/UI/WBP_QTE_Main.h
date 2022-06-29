// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "QTEPlugins/Data/FStartQTEStruct.h"
#include "WBP_QTE_Main.generated.h"

/**
 * 
 */
UCLASS()
class QTEPLUGINS_API UWBP_QTE_Main : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UPROPERTY(meta=(BindWidget))
	UNamedSlot* NamedSlot;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel*CanvasPanel;

	
	UPROPERTY()
	class UGameInstanceSubsystem_QTE * GameInstanceSubsystem_QTE;
public:
	
	UFUNCTION(BlueprintCallable)
	void Start(FStartQTEStruct const &Data );

	UFUNCTION(BlueprintCallable)
	void End(bool bSuccess);

	UFUNCTION(BlueprintImplementableEvent)
	void SuccessEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void FailEvent();
};
