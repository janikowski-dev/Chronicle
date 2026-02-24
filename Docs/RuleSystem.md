# Rule System

**Rule System** is an asset-based rules editor for Unreal Engine, built as part of **Chronicle**. It allows you to create custom **Conditions** and **Callbacks** that can be used in other gameplay systems.

## Example

![Rule System Overview 1](../Assets/Rule_System_Overview_1.png)

![Rule System Overview 2](../Assets/Rule_System_Overview_2.png)

## How To Use

### Add a callback

1. Create the directory: `Game/Rules/Callbacks`
2. Right-click in the Content Browser within that directory
3. Select **Chronicle → Rule Asset**

### Add a condition

1. Create the directory: `Game/Rules/Conditions`
2. Right-click in the Content Browser within that directory
3. Select **Chronicle → Rule Asset**

### Modify rule

1. Each rule has a **unique GUID** for identification
2. Double-click a rule to modify its **name**

## Integration

To integrate with runtime systems, use **URuleAsset** instances. These assets provide a structured way to define and access rules at runtime, ensuring consistent behavior across your dialogue system.

## Planned Features

- **Validator** – Detect conflicts or unused rules
- **Browser** – Visual exploration of all rules