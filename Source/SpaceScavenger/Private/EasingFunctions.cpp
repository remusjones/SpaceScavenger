#include "EasingFunctions.h"

float UEasingFunctions::EaseInSine(const float Input)
{
	return 1 - FMath::Cos(Input * UE_PI) / 2;
}

float UEasingFunctions::EaseOutSine(const float Input)
{
	return FMath::Cos(Input * UE_PI) / 2;
}

float UEasingFunctions::EaseInOutSine(const float Input)
{
	return -(FMath::Cos(UE_PI * Input) - 1) / 2;
}

float UEasingFunctions::EaseInQuad(float Input)
{
	return Input * Input;
}

float UEasingFunctions::EaseOutQuad(float Input)
{
	return 1 - (1 - Input) * (1 - Input);
}

float UEasingFunctions::EaseInOutQuad(const float Input)
{
	return Input < 0.5 ? 2 * Input * Input : 1 - FMath::Pow(-2 * Input + 2, 2) / 2;
}

float UEasingFunctions::EaseInCubic(const float Input)
{
	return Input * Input * Input;
}

float UEasingFunctions::EaseOutCubic(const float Input)
{
	return 1 - FMath::Pow(1 - Input, 3);
}

float UEasingFunctions::EaseInOutCubic(const float Input)
{
	return Input < 0.5 ? 4 * Input * Input * Input : 1 - FMath::Pow(-2 * Input + 2, 3) / 2;
}

float UEasingFunctions::EaseInQuart(const float Input)
{
	return Input * Input * Input * Input;
}

float UEasingFunctions::EaseOutQuart(const float Input)
{
	return 1 - FMath::Pow(1 - Input, 4);
}

float UEasingFunctions::EaseInOutQuart(const float Input)
{
	return Input < 0.5 ? 8 * Input * Input * Input * Input : 1 - FMath::Pow(-2 * Input + 2, 4) / 2;
}

float UEasingFunctions::EaseInQuint(const float Input)
{
	return Input * Input * Input * Input * Input;
}

float UEasingFunctions::EaseOutQuint(const float Input)
{
	return FMath::Sqrt(1 - FMath::Pow(Input - 1, 2));
}

float UEasingFunctions::EaseInOutQuint(const float Input)
{
	return Input < 0.5 ? 16 * Input * Input * Input * Input * Input : 1 - FMath::Pow(-2 * Input + 2, 5) / 2;
}

float UEasingFunctions::EaseInExpo(const float Input)
{
	return Input == 0 ? 0 : FMath::Pow(2, 10 * Input - 10);
}

float UEasingFunctions::EaseOutExpo(const float Input)
{
	return Input == 1 ? 1 : 1 - FMath::Pow(2, -10 * Input);
}

float UEasingFunctions::EaseInOutExpo(const float Input)
{
	return Input == 0
	? 0
	: Input == 1
	? 1
	: Input < 0.5 ? FMath::Pow(2, 20 * Input - 10) / 2
	: (2 - FMath::Pow(2, -20 * Input + 10)) / 2;
}

float UEasingFunctions::EaseInCirc(const float Input)
{
	return 1 - FMath::Sqrt(1 - FMath::Pow(Input, 2));
}

float UEasingFunctions::EaseOutCirc(const float Input)
{
	return FMath::Sqrt(1 - FMath::Pow(Input - 1, 2));
}

float UEasingFunctions::EaseInOutCirc(const float Input)
{
	return Input < 0.5
  ? (1 - FMath::Sqrt(1 - FMath::Pow(2 * Input, 2))) / 2
  : (FMath::Sqrt(1 - FMath::Pow(-2 * Input + 2, 2)) + 1) / 2;
}

float UEasingFunctions::EaseInBack(const float Input)
{
	constexpr float C1 = 1.70158f;
	constexpr float C3 = C1 + 1;

	return C3 * Input * Input * Input - C1 * Input * Input;
}

float UEasingFunctions::EaseOutBack(const float Input)
{
	constexpr float C1 = 1.70158f;
	constexpr float C3 = C1 + 1;

	return 1 + C3 * FMath::Pow(Input - 1, 3) + C1 * FMath::Pow(Input - 1, 2);
}

float UEasingFunctions::EaseInOutBack(const float Input)
{
	constexpr float C1 = 1.70158f;
	constexpr float C2 = C1 * 1.525f;

	return Input < 0.5
	  ? (FMath::Pow(2 * Input, 2) * ((C2 + 1) * 2 * Input - C2)) / 2
	  : (FMath::Pow(2 * Input - 2, 2) * ((C2 + 1) * (Input * 2 - 2) + C2) + 2) / 2;
}

float UEasingFunctions::EaseInElastic(const float Input)
{
	constexpr float C4 = 2 * UE_PI / 3;

	return Input == 0
	  ? 0
	  : Input == 1
	  ? 1
	  : -FMath::Pow(2, 10 * Input - 10) * FMath::Sin((Input * 10 - 10.75f) * C4);
}

float UEasingFunctions::EaseOutElastic(const float Input)
{
	constexpr float C4 = 2 * UE_PI / 3;

	return Input == 0
	  ? 0
	  : Input == 1
	  ? 1
	  : FMath::Pow(2, -10 * Input) * FMath::Sin((Input * 10 - 0.75f) * C4) + 1;
}

float UEasingFunctions::EaseInOutElastic(const float Input)
{
	constexpr float C5 = (2 * UE_PI) / 4.5f;

	return Input == 0
	  ? 0
	  : Input == 1
	  ? 1
	  : Input < 0.5
	  ? -(FMath::Pow(2, 20 * Input - 10) * FMath::Sin((20 * Input - 11.125) * C5)) / 2
	  : FMath::Pow(2, -20 * Input + 10) * FMath::Sin((20 * Input - 11.125) * C5) / 2 + 1;
}

float UEasingFunctions::EaseInBounce(const float Input)
{
	return 1 - EaseOutBounce(1 - Input);
}

float UEasingFunctions::EaseOutBounce(const float Input)
{
	float X = Input;
	constexpr float N1 = 7.5625f;
	constexpr float D1 = 2.75f;

	if (X < 1 / D1) {
		return N1 * X * X;
	}
	if (X < 2 / D1) {
		return N1 * (X -= 1.5f / D1) * X + 0.75f;
	}
	if (X < 2.5f / D1) {
		return N1 * (X -= 2.25f / D1) * X + 0.9375f;
	}
	return N1 * (X -= 2.625f / D1) * X + 0.984375f;
}

float UEasingFunctions::EaseInOutBounce(const float Input)
{
	return Input < 0.5
	? (1 - EaseOutBounce(1 - 2 * Input)) / 2
	: (1 + EaseOutBounce(2 * Input - 1)) / 2;
}
