#include "SDialogueNode.h"

#include "Nodes/Unreal/UDialogueNode.h"
#include "Pins/SDialogueGraphPin.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "SGraphPanel.h"
#include "Graphs/UDialogueGraph.h"

void SDialogueNode::MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty)
{
}

TSharedPtr<SGraphPin> SDialogueNode::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SNew(SDialogueGraphPin, Pin);
}

TSharedPtr<SGraphPin> SDialogueNode::GetHoveredPin(const FGeometry&, const FPointerEvent&) const
{
	return nullptr;
}

void SDialogueNode::UpdateGraphNode()
{
	SGraphNode::UpdateGraphNode();
	SetupErrorReporting();

	const TSharedRef<SVerticalBox> RegularView = SNew(SVerticalBox);
	const TSharedRef<SVerticalBox> CollapsedView = SNew(SVerticalBox);
	const TSharedRef<SWidget> HiddenView = SNew(SSpacer);
	
	SAssignNew(LeftNodeBox, SVerticalBox);
	SAssignNew(RightNodeBox, SVerticalBox);

	AddHeader(CollapsedView);
	AddHeader(RegularView);
	AddBody(RegularView);
	
	SAssignNew(WidgetSwitcher, SWidgetSwitcher)
	.WidgetIndex(this, &SDialogueNode::GetBodyIndex)
	+ SWidgetSwitcher::Slot()
	[
		RegularView
	]

	+ SWidgetSwitcher::Slot()
	[
		CollapsedView
	]

	+ SWidgetSwitcher::Slot()
	[
		HiddenView
	];

	RemoveSlot(ENodeZone::Center);
	
	GetOrAddSlot(ENodeZone::Center)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("Graph.Node.Body"))
		.BorderBackgroundColor(this, &SDialogueNode::GetHeaderColor)
		[
			WidgetSwitcher.ToSharedRef()
		]
	];
	
	CreatePinWidgets();
}

void SDialogueNode::AddHeader(const TSharedRef<SVerticalBox>& Box)
{
	const FText Title = Cast<UDialogueNode>(GraphNode)->GetTitle();
	
	Box->AddSlot()
	.AutoHeight()
	[
		SNew(SOverlay)
		
		+ SOverlay::Slot()
		[
			SNew(SBox)
			.WidthOverride(275.0f)
			.Padding(4)
			[
				SNew(STextBlock)
				.Text(Title)
			]
		]

		+ SOverlay::Slot()
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.Padding(FMargin(0.0f, 4.0f))
			.AutoWidth()
			[
				LeftNodeBox.ToSharedRef()
			]
			
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				SNew(SSpacer)
			]

			+ SHorizontalBox::Slot()
			.Padding(FMargin(0.0f, 4.0f))
			.AutoWidth()
			[
				RightNodeBox.ToSharedRef()
			]
		]

		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		[
			SNew(SButton)
			.ButtonStyle(FAppStyle::Get(), "HoverHintOnly")
			.ContentPadding(FMargin(4))
			.ClickMethod(EButtonClickMethod::MouseDown)
			.OnClicked(this, &SDialogueNode::ToggleCollapse)
			[
				SNew(SImage)
				.Image_Lambda([this]()
				{
					return TypedNode->bIsCollapsed
						? FAppStyle::Get().GetBrush("Icons.ChevronRight")
						: FAppStyle::Get().GetBrush("Icons.ChevronDown");
				})
			]
		]
	];
}

FReply SDialogueNode::ToggleCollapse() const
{
	ToggleCollapsedState();
	ApplyCollapse();
	RefreshGraph();
	return FReply::Handled();
}

void SDialogueNode::ApplyCollapse() const
{
	TSet<UDialogueNode*> Visited;
	ApplyCollapse(TypedNode.Get(), false, Visited);
}

void SDialogueNode::ApplyCollapse(
	UDialogueNode* CurrentNode,
	const bool bParentHidden,
	TSet<UDialogueNode*>& Visited
) const
{
	if (!CurrentNode || Visited.Contains(CurrentNode))
	{
		return;
	}

	Visited.Add(CurrentNode);
	CurrentNode->bIsHidden = bParentHidden;
	const bool bHideChildren = bParentHidden || CurrentNode->bIsCollapsed;

	for (UEdGraphPin* Pin : CurrentNode->Pins)
	{
		if (Pin->Direction != EGPD_Output)
		{
			continue;
		}

		for (const UEdGraphPin* LinkedPin : Pin->LinkedTo)
		{
			if (UDialogueNode* ChildNode = Cast<UDialogueNode>(LinkedPin->GetOwningNode()))
			{
				ApplyCollapse(ChildNode, bHideChildren, Visited);
			}
		}
	}
}

void SDialogueNode::ToggleCollapsedState() const
{
	TypedNode->bIsCollapsed = !TypedNode->bIsCollapsed;
}

void SDialogueNode::RefreshGraph() const
{
	const UDialogueGraph* TypedGraph = Cast<UDialogueGraph>(GraphNode->GetGraph());
	TypedGraph->Refresh();
}

int SDialogueNode::GetBodyIndex() const
{
	if (TypedNode->bIsCollapsed)
	{
		return Collapsed;
	}

	if (TypedNode->bIsHidden)
	{
		return Hidden;
	}
	
	return Regular;
}

void SDialogueNode::Cache(UEdGraphNode* Node)
{
	TypedNode = Cast<UDialogueNode>(Node);
	GraphNode = Node;
}
