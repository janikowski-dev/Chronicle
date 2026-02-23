#pragma once

#include "FCharacterSet.h"

class CHARACTERSYSTEMEDITOR_API FCharacterDirectory
{
public:
	static FCharacterSet& GetAll();
	static void Refresh();
	
private:
	static FCharacterSet All;
};
