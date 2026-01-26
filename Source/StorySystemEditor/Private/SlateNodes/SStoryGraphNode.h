#pragma once

#include "SGraphNode.h"

class SStoryGraphPin;

class SStoryGraphNode : public SGraphNode
{
public:
	virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true ) override;
	virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;
	virtual TSharedPtr<SGraphPin> GetHoveredPin(
		const FGeometry& MyGeometry,
		const FPointerEvent& MouseEvent
	) const override;
};
