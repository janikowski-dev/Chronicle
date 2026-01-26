#pragma once

#include "SGraphPin.h"

class SStoryGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SStoryGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);
	virtual const FSlateBrush* GetPinIcon() const override;
};