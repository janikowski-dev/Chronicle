#include "SRuleTagNode.h"

#include "GameplayTagsManager.h"
#include "Nodes/Unreal/URuleTagNode.h"

void SRuleTagNode::Construct(const FArguments&, URuleTagNode* InNode)
{
	TypedNode = Cast<URuleTagNode>(InNode);
	GraphNode = InNode;

	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	FGameplayTagContainer Container;
	Manager.RequestAllGameplayTags(Container, false);

	AllTags.Empty();
	
	for (const FGameplayTag& GameplayTag : Container.GetGameplayTagArray())
	{
		FString TagName = GameplayTag.GetTagName().ToString();
		AllTags.Add(MakeShared<FString>(TagName));
	}

	if (AllTags.Num() > 0)
	{
		SelectedTag = AllTags[0];
	}
	
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
					SNew(SComboBox<TSharedPtr<FString>>)
					.OptionsSource(&AllTags)
					.OnGenerateWidget_Lambda([](const TSharedPtr<FString>& InItem)
					{
						return SNew(STextBlock).Text(FText::FromString(*InItem));
					})
					.OnSelectionChanged_Lambda([this](const TSharedPtr<FString>& NewSelection, ESelectInfo::Type)
					{
						SelectedTag = NewSelection;
					})
					.InitiallySelectedItem(SelectedTag)
					[
						SNew(STextBlock)
						.Text_Lambda([this]() -> FText
						{
							return SelectedTag.IsValid() ? FText::FromString(*SelectedTag) : FText::FromString("Select...");
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
