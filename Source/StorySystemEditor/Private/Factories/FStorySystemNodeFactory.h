#pragma once

#include "EdGraphUtilities.h"

class FStorySystemNodeFactory : public FGraphPanelNodeFactory
{
public:
	virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};
