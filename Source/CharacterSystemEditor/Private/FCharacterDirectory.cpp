#include "FCharacterDirectory.h"

FCharacterSet FCharacterDirectory::All(FName("/Game/Characters"));

FCharacterSet& FCharacterDirectory::GetAll()
{
	return All;
}

void FCharacterDirectory::Refresh()
{
	All.Refresh();
}
