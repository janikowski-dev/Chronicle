#include "SRuleDefaultNode.h"

#include "Nodes/Unreal/URuleInputNode.h"

void SRuleDefaultNode::Construct(const FArguments&, URuleNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
}

void SRuleDefaultNode::UpdateGraphNode()
{
	SetupErrorReporting();

	RemoveSlot(ENodeZone::Center);

	GetOrAddSlot(ENodeZone::Center)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("Graph.Node.Body"))
		.BorderBackgroundColor(TypedNode->GetBackgroundColor())
		[
			SNew(SVerticalBox)
			
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBox)
				.Padding(4)
				[
					SNew(STextBlock)
					.Text(TypedNode->GetTitle())
				]
			]
			
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
			
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SAssignNew(LeftNodeBox, SVerticalBox)
				]
				
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					SNew(SSpacer)
				]
			
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SAssignNew(RightNodeBox, SVerticalBox)
				]
			]
		]
	];
	
	CreatePinWidgets();
}

void SRuleDefaultNode::Cache(URuleNode* InNode)
{
	TypedNode = Cast<URuleNode>(InNode);
	GraphNode = InNode;
}
