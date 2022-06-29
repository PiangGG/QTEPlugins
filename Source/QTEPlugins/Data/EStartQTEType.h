#pragma once

UENUM(BlueprintType)
enum class EStartQTEType :uint8
{
	Point		UMETA(DisplayName = "点击"),
	Line		UMETA(DisplayName = "滑动"),
	Ring		UMETA(DisplayName = "画环"),
};
