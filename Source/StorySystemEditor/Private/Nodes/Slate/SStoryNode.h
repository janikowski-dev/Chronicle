#pragma once

#include "SGraphNode.h"
#include "Nodes/Unreal/UStoryNode.h"

enum ENodeViewType : int32
{
	Regular = 0,
	Collapsed = 1,
	Hidden = 2
};

class SStoryNode : public SGraphNode
{
public:
	virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;
	virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;
	virtual TSharedPtr<SGraphPin> GetHoveredPin(const FGeometry&, const FPointerEvent&) const override;
	virtual FReply OnMouseButtonDoubleClick(const FGeometry&, const FPointerEvent&) override;
	virtual void UpdateGraphNode() override;

protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) = 0;
	virtual FText GetTitle(UStoryNode* Node) = 0;
	virtual FSlateColor GetHeaderColor() const = 0;
	void Cache(UEdGraphNode* Node);

private:
	void AddHeader(const TSharedRef<SVerticalBox>& Box);
	void ApplyCollapse(
		UEdGraphNode* CurrentNode,
		UEdGraphNode* RootNode,
		TSet<UEdGraphNode*>& Visited
	) const;
	FReply ToggleCollapse();
	void OpenNodeEditor() const;
	int GetBodyIndex() const;
	
public:
	TSharedPtr<SWidgetSwitcher> WidgetSwitcher;
	bool bIsCollapsed = false;
	bool bIsHidden = false;
};
