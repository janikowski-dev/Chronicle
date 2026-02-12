#pragma once

#include "FDialogueNodeFactory.h"
#include "Nodes/Slate/SDialogueLineNode.h"
#include "Nodes/Slate/SDialogueRootNode.h"
#include "Nodes/Slate/SDialogueResponseNode.h"
#include "Nodes/Unreal/UDialogueLineNode.h"
#include "Nodes/Unreal/UDialogueResponseNode.h"
#include "Nodes/Unreal/UDialogueRootNode.h"

TSharedPtr<SGraphNode> FDialogueNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (UDialogueLineNode* TypedNode = Cast<UDialogueLineNode>(Node))
	{
		return SNew(SDialogueLineNode, TypedNode);
	}
		
	if (UDialogueRootNode* TypedNode = Cast<UDialogueRootNode>(Node))
	{
		return SNew(SDialogueRootNode, TypedNode);
	}
		
	if (UDialogueResponseNode* TypedNode = Cast<UDialogueResponseNode>(Node))
	{
		return SNew(SDialogueResponseNode, TypedNode);
	}
		
	return nullptr;
}
