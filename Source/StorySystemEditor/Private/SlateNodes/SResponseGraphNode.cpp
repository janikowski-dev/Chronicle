#include "SResponseGraphNode.h"
#include "Nodes/UResponseGraphNode.h"

void SResponseGraphNode::Construct(const FArguments&, UResponseGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

void SResponseGraphNode::UpdateGraphNode()
{
	SetupErrorReporting();

	const TSharedRef<SWidget> NodeBody =
	SNew(SBox)
	.WidthOverride(275.0f)
	.HeightOverride(150.0f)
	[
		SNew(SVerticalBox)

		// Title
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Response")))
		]

		// Pins row
		+ SVerticalBox::Slot()
		.FillHeight(1.0f) // IMPORTANT
		.Padding(2)
		[
			SNew(SHorizontalBox)

			// In pins
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

			// Out pins
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SAssignNew(RightNodeBox, SVerticalBox)
			]
		]
	];

	this->GetOrAddSlot(ENodeZone::Center)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("Graph.Node.Body"))
		[
			NodeBody
		]
	];

	CreatePinWidgets();
}
