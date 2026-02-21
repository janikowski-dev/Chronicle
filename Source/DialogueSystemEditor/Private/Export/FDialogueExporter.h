#pragma once

#include "Data/FDialogueNodeData.h"

class UDialogueData;
class UDialogueNode;
class URuleNode;
class UDialogueAsset;

class FDialogueExporter
{
public:
	static void CopyToClipboard(const UDialogueAsset* Asset);
	static void ExportToAsset(const UDialogueAsset* Asset);

private:
	static UDialogueData* ConvertToAsset(const UDialogueAsset* Asset);
	static UDialogueData* ConvertToTemporaryAsset(const UDialogueAsset* Asset);
	static UDialogueData* PopulateData(UDialogueData* Data, const UDialogueAsset* Asset);
	static FDialogueNodeData PopulateNodeData(UDialogueNode* Node, UDialogueData* Data);
	static int32 PopulateRuleData(URuleNode* Rule, UDialogueData* Data);
};