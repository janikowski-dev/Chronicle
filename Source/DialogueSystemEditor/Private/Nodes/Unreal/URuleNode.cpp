#include "URuleNode.h"

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

bool URuleNode::CanUserDeleteNode() const
{
	return true;
}
