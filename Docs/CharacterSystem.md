# Character System

**Character System** is an asset-based character editor for Unreal Engine, built as part of **Chronicle**. It allows you to create custom **Characters** that can be used in other gameplay systems.

## Example

![Character System Overview](Assets/Character_System_Overview.png)

## How To Set Up

### Add a character

1. Create the directory: `Game/Characters`
2. Right-click in the Content Browser within that directory
3. Select **Miscellaneous → Data Asset**
4. Search for the **Character Asset** type
5. Click **Select** to create a new character

### Modify character

1. Each character has a **unique GUID** for identification
2. Double-click a character to modify its **name**

## How To Use In Code

Access chraracters programmatically using the `FCharacterDirectory`:

```cpp
// Fetch all characters from directory
FCharacterDirectory::Refresh();

// Get all character IDs
auto CharacterIds = FCharacterDirectory::GetConditions()->GetSharedIds(); 
 
// Get a character name by ID
auto CharacterName = FCharacterDirectory::GetAll()->GetName(MyGuid);
```

## Planned Features

- **Validator** – Detect conflicts or unused characters
- **Browser** – Visual exploration of all characters