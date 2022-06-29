#pragma once

#include "EStartQTEType.h"
#include "Engine/DataTable.h"
#include "FStartQTEStruct.generated.h"

USTRUCT(BlueprintType)
struct FStartQTEStruct:public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="StartQTEData",meta=(DisplayName="屏幕位置"))
	FVector2D Location;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="StartQTEData",meta=(DisplayName="变换角度"))
	float Angle;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="StartQTEData",meta=(DisplayName="持续时间"))
	float MaxTime;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="StartQTEData",meta=(DisplayName="QTE类型"))
	EStartQTEType Type;
	
	FStartQTEStruct()
	{
		Location = FVector2D(0.0F,0.0F);
		Angle = 0.0F;
		MaxTime = 2.0F;
		Type = EStartQTEType::Point;
	}
	FStartQTEStruct(FVector2D location,float angle,float maxTime,EStartQTEType type)
	{
		Location = location;
		Angle = angle;
		MaxTime = maxTime;
		Type = type;
	}
};
