#include "URuleNode.h"

void URuleNode::PostPlacedNewNode()
{
	Super::PostPlacedNewNode();
	AssignId();
}

bool URuleNode::CanUserDeleteNode() const
{
	return true;
}

bool URuleNode::AllowMultipleInputs() const
{
	return false;
}

FText URuleNode::GetTitle() const
{
	return FText::GetEmpty();
}

FSlateColor URuleNode::GetBackgroundColor() const
{
	return FSlateColor();
}

void URuleNode::AssignId()
{
	if (Id.IsValid())
	{
		return;
	}
	
	Id = FGuid::NewGuid();
}
