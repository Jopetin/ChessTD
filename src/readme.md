# Source content

The 'src' folder contains all of the source code for the project. It is mostly divided into folders for specific modules:

## Folders

### tiles

Contains the implementations of different tiles that the game field consists of. Enemies and towers are placed in their representive tiles.

### towers

Contains the implementations of different towers that the player can place in order to shoot enemies and stop their advance.

### enemies

Contains the implementations of different enemies, that move through the path tiles in the map and are shot at by the towers.

### GUI

Contains the graphical interface elements that the main game uses to visualize the game for the player.

### maps

Contains the maps used in the game in a custom text format.

## Separate files

The rest of the files in 'src' can be roughly categorized into map building tools, exceptions and the main Game.cpp file which is where the game actually runs.