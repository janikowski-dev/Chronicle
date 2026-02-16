#pragma once

#include "FRuleNodeFactory.h"

#include "Nodes/Slate/SRuleDefaultNode.h"
#include "Nodes/Slate/SRuleCallbackNode.h"
#include "Nodes/Slate/SRuleConditionNode.h"
#include "Nodes/Unreal/URuleCallbackNode.h"
#include "Nodes/Unreal/URuleConditionNode.h"

TSharedPtr<SGraphNode> FRuleNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (URuleCallbackNode* TypedNode = Cast<URuleCallbackNode>(Node))
	{
		return SNew(SRuleCallbackNode, TypedNode);
	}
	
	if (URuleConditionNode* TypedNode = Cast<URuleConditionNode>(Node))
	{
		return SNew(SRuleConditionNode, TypedNode);
	}
	
	if (URuleNode* TypedNode = Cast<URuleNode>(Node))
	{
		return SNew(SRuleDefaultNode, TypedNode);
	}
	
	return nullptr;
}
