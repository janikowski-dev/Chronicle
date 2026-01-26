#include "SStoryGraphNode.h"

#include "Pins/SStoryGraphPin.h"

void SStoryGraphNode::MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty)
{
}

TSharedPtr<SGraphPin> SStoryGraphNode::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SNew(SStoryGraphPin, Pin);
}

TSharedPtr<SGraphPin> SStoryGraphNode::GetHoveredPin(
	const FGeometry& MyGeometry,
	const FPointerEvent& MouseEvent
) const
{
	return nullptr;
}
