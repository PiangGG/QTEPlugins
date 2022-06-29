// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QTEPlugins/Data/FStartQTEStruct.h"
#include "WBP_QTE_Point.generated.h"

/**
 * 
 */
UCLASS()
class QTEPLUGINS_API UWBP_QTE_Point : public UUserWidget
{
	GENERATED_BODY()

public:
	//UWBP_QTE_Point();
	virtual bool Initialize() override;
	
	UPROPERTY(meta=(BindWidget))
	class UButton * PointButton;

	UPROPERTY(meta=(BindWidget))
	class UImage* TimeLineImage;

	UPROPERTY(meta=(BindWidget))
	class UImage* DynamicImage;

	/*UPROPERTY(meta=(BindWidget))
	class UWidgetAnimation* PointDynamicAnimation;*/
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(DisplayName="QTE按钮风格"))
	FButtonStyle PointButtonStyle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(DisplayName="QTE插值速度"))
	float InterpSpeed = 1.0f;
	
	void Start(FStartQTEStruct const &Data);

	UFUNCTION(BlueprintCallable)
	void End();
	
	void Init();
protected:
	void PointButtonOnClick();

	
private:
	//qte倒计时 时间句柄
	FTimerHandle TH_CountDown;

	float CurrentTime;

	UPROPERTY()
	UMaterialInterface*MaterialInterface;
	UPROPERTY()
	UMaterialInstanceDynamic * MaterialInstanceDynamic;
private:
	void UpdatePersent();
};
