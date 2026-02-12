#pragma once

#include "SGraphPin.h"

class SDialogueGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);
	virtual const FSlateBrush* GetPinIcon() const override;
};