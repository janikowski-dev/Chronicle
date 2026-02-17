#include "SRuleTagNode.h"

#include "FRuleDirectory.h"
#include "Nodes/Unreal/URuleTagNode.h"

void SRuleTagNode::Construct(const FArguments&, URuleTagNode* InNode, const FRuleSet& Set)
{
	Cache(Set);
	Cache(InNode);
	UpdateGraphNode();
}

void SRuleTagNode::UpdateGraphNode()
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
					SNew(SComboBox<TSharedPtr<FGuid>>)
					
					.OptionsSource(&Ids)
					.OnGenerateWidget_Lambda([this](const TSharedPtr<FGuid>& InItem)
					{
						return SNew(STextBlock)
							.Text(FText::FromName(RuleSet->GetName(*InItem)));
					})
					.OnSelectionChanged_Lambda([this](const TSharedPtr<FGuid>& NewSelection, ESelectInfo::Type)
					{
						TypedNode->TagId = *NewSelection;
					})
					[
						SNew(STextBlock)
						.Text_Lambda([this]() -> FText
						{
							return RuleSet->IsValid(TypedNode->TagId) ?
								FText::FromName(RuleSet->GetName(TypedNode->TagId)) :
								FText::FromString("Select...");
						})
					]
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

void SRuleTagNode::Cache(URuleTagNode* InNode)
{
	TypedNode = Cast<URuleTagNode>(InNode);
	GraphNode = InNode;
}

void SRuleTagNode::Cache(const FRuleSet& Set)
{
	RuleSet = const_cast<FRuleSet*>(&Set);
	Ids = Set.GetSharedIds();
}
