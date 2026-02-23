# Story System

**Story System** is an Unreal Engine plugin for building narrative-driven games. It gives developers a visual way to create branching dialogues, hook up game logic through a rule system, and eventually manage characters, quests, and cinematic timelines — all from within the editor.

## Dialogue Graph

### Current Features

-   **Branching Dialogue Paths**

    ![Overview_Example](Assets/Overview_Example.png)

-   **Node Collapsing**

    ![Overview Collapse](Assets/Overview_Collapse.png)
    
-   **Node Inner Graph**
    
    -   Requirements for node availability
  
        ![Requirements](Assets/Requirements_Inner_Visuals.png)
        
    -   Callbacks after node
 
        ![Callbacks](Assets/Callbacks_Inner_Visuals.png)

-   **Inner State Visualization: Key - Requirements & Link - Callbacks**

    ![Requirements Outer Visuals](Assets/Requirements_Outer_Visuals.png)

    ![Callbacks Outer Visuals](Assets/Callbacks_Outer_Visuals.png)

### How To Use

-   **Create Dialogue Graph:**

    ![Tutorial Create](Assets/Tutorial_Create.gif)

-   **Open Dialogue Graph:** Double LMB on `Dialogue Asset`

-   **Add Participants:**

    ![Tutorial Participants](Assets/Tutorial_Participants.gif)

-   **Add Nodes:**

    ![Tutorial Nodes](Assets/Tutorial_Nodes.gif)

-   **Add Requirements:**

    ![Tutorial Requirements](Assets/Tutorial_Requirements.gif)

-   **Add Callbacks:**

    ![Tutorial Callbacks](Assets/Tutorial_Callbacks.gif)

-   **Export To Runtime UObject:**

    ![Tutorial UObject](Assets/Tutorial_UObject.gif)

-   **Copy JSON To Clipboard:**

    ![Tutorial JSON](Assets/Tutorial_JSON.gif)

# Rule System (On Hold)

### Current Features

- Asset-based rules creation
- GUID-oriented rule recognition

### How To Use

-   **Create Rule (Inside `Game/Rules/Conditions` Or Inside `Game/Rules/Callbacks`):**

    ![Tutorial Rules](Assets/Tutorial_Rules.gif)

### Planned Features

- Browser for rules
- Validator

# Character System

### Current Features

- Asset-based character creation
- GUID-oriented character recognition

### How To Use

-   **Create Character (Inside `Game/Characters`):**

    ![Tutorial Characters](Assets/Tutorial_Characters.gif)

### Planned Features

- Browser for characters
- Validator

## Roadmap

1.  Cinematic Timeline
2.  Quest Editor

## Getting Started

> Instructions will be added soon once core systems stabilize.

## Contributing

Story System is open for contributions! If you'd like to help expand features, improve documentation, or provide bug fixes, please fork the repository and submit a pull request.
