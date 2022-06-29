// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QTEPlugins/Data/FStartQTEStruct.h"
#include "WBP_QTE_Line.generated.h"

/**
 * 
 */
UCLASS()
class QTEPLUGINS_API UWBP_QTE_Line : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual bool Initialize() override;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(BindWidget))
	class USlider * Sliderbar;

	UPROPERTY(meta=(BindWidget))
	class UImage* Image_bg;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar*ProgressBar;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(DisplayName="QTE滑条时间样式"))
	FProgressBarStyle ProgressBarStyle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(DisplayName="QTE滑条滑动样式"))
	FSliderStyle SliderStyle;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(DisplayName="QTE插值速度"))
	float InterpSpeed = 1.0f;
	
	void Start(FStartQTEStruct const &Data);

	UFUNCTION(BlueprintCallable)
	void End();
	
	void Init();
protected:
	//void PointButtonOnClick();

	
private:
	//qte倒计时 时间句柄
	FTimerHandle TH_CountDown;

	float MaxTime;
	
	float CurrentTime;

	UPROPERTY()
	UMaterialInterface*MaterialInterface;
	UPROPERTY()
	UMaterialInstanceDynamic * MaterialInstanceDynamic;
private:
	void UpdatePersent();
};
