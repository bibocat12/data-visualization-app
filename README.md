# Data Structures Visualizer

**Data Structures Visualizer** is an tool that visualizes the internal operations of basic data structures such as linked lists, heaps, tries, graphs. The project is built using **C++** and the **SFML** graphics library, from the **Data Structures (CS163)** course at the University of Science – VNU-HCM.

---

##  Key Features

-  Visualize data structures with smooth animations.
-  Supports fundamental operations: insert, delete, search, update.
-  Adjustable animation speed for better understanding.
-  Step-by-step algorithm explanation displayed on screen.
-  Intuitive, student-friendly graphical interface.
-  Ability to reset or replay operations at any time.

---

##  Supported Data Structures

- Singly Linked List  
- Heap  
- AVL Tree  
- 2-3-4 Tree  
- Trie  
- Graph 

---

## Technologies Used

- **Language:** C++17  
- **Graphics Library:** [SFML 2.6.0](https://www.sfml-dev.org)  
- **Build System:** CMake  
- **IDE:** Visual Studio / VS Code  

---

## Installation & Running

### Requirements

- CMake ≥ 3.28 
- SFML 2.6.0 (automatically downloaded via CMake)  
- C++ compiler with C++17 support

### Build and Run (Command Line)

```bash
git clone https://github.com/bibocat12/data-visualization-app
cd data-visualization-app

# Create a build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Compile
cmake --build . --config Release

# Run the executable
./bin/main      # or replace 'main' with your executable name
