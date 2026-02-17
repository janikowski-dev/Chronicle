#pragma once

#include "FRuleNodeFactory.h"

#include "FRuleDirectory.h"
#include "Nodes/Slate/SRuleDefaultNode.h"
#include "Nodes/Slate/SRuleTagNode.h"
#include "Nodes/Unreal/URuleCallbackNode.h"
#include "Nodes/Unreal/URuleConditionNode.h"

TSharedPtr<SGraphNode> FRuleNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (URuleCallbackNode* TypedNode = Cast<URuleCallbackNode>(Node))
	{
		return SNew(SRuleTagNode, TypedNode, FRuleDirectory::GetCallbacks());
	}
	
	if (URuleConditionNode* TypedNode = Cast<URuleConditionNode>(Node))
	{
		return SNew(SRuleTagNode, TypedNode, FRuleDirectory::GetConditions());
	}
	
	if (URuleNode* TypedNode = Cast<URuleNode>(Node))
	{
		return SNew(SRuleDefaultNode, TypedNode);
	}
	
	return nullptr;
}
