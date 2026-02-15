#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "URuleGraph.generated.h"

enum class EOutputType : int8;
class URuleNode;

UCLASS()
class DIALOGUESYSTEMEDITOR_API URuleGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	TArray<URuleNode*> GetRules(EOutputType Type) const;

private:
	URuleNode* GetOutputNode(const EOutputType Type) const;
	void GetRules(URuleNode* Node, TArray<URuleNode*>& Rules) const;
};
