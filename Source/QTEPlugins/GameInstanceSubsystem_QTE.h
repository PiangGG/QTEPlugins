// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FStartQTEStruct.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/WBP_QTE_Main.h"
#include "GameInstanceSubsystem_QTE.generated.h"

/**
 * 
 */
UCLASS()
class QTEPLUGINS_API UGameInstanceSubsystem_QTE : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UGameInstanceSubsystem_QTE();
	UFUNCTION(BlueprintCallable,Category=QTE)
	void Start(FStartQTEStruct const &Data);
	UFUNCTION(BlueprintCallable,Category=QTE)
	void End(bool bSuccess);
	
	UPROPERTY()
	TSubclassOf<UWBP_QTE_Main>QTEWidet;

	UPROPERTY()
	APlayerController * PlayerController = nullptr;
	
	UPROPERTY()
	UWBP_QTE_Main* QTEMain = nullptr;

	/*能创建的种类*/
	UPROPERTY()
	TSubclassOf<class UWBP_QTE_Point> QTEWidet_Point;
	UPROPERTY()
	class UWBP_QTE_Point* QTE_Point;

	UPROPERTY()
	TSubclassOf<class UWBP_QTE_Line> QTEWidet_Line;
	UPROPERTY()
	class UWBP_QTE_Line* QTE_Line;
private:
	bool bStartQTEing = false;

	
	
};
