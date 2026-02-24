# Character System

**Character System** is an asset-based character editor for Unreal Engine, built as part of **Chronicle**. It allows you to create custom **Characters** that can be used in other gameplay systems.

## Example

![Character System Overview](../Assets/Character_System_Overview.png)

## How To Use

### Add a character

1. Create the directory: `Game/Characters`
2. Right-click in the Content Browser within that directory
3. Select **Chronicle → Character Asset**

### Modify character

1. Each character has a **unique GUID** for identification
2. Double-click a character to modify its **name**

## Integration

To integrate with runtime systems, use **UCharacterAsset** instances. These assets provide a structured way to define and access rules at runtime, ensuring consistent behavior across your dialogue system.

## Planned Features

- **Validator** – Detect conflicts or unused characters
- **Browser** – Visual exploration of all characters