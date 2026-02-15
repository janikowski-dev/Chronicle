#pragma once

struct FColors
{
	static constexpr FLinearColor TurquoiseLinear{0.0f, 1.0f, 1.0f};
	static constexpr FLinearColor PurpleLinear{0.7f, 0.3f, 1.0f};

	inline static const FSlateColor Turquoise{TurquoiseLinear};
	inline static const FSlateColor Purple{PurpleLinear};
};