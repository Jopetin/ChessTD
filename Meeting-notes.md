# Meeting 1 (16.11.2022 10:00)

## Attendees
Joel Toppinen

Miikka Åsnabrygg

Petrus Nikoskinen

Petteri Kippo

## Summary of works

Joel created the CMake configuration and everyone else tested it works on their home enviroment. We now have a working baseline from which everyone can start their development.

## Challenges

SFML gives some complaints regarding vertical sync, possibly having to do with being run from WSL. Currently does not seem important and will be disregarded for now.

## Actions

We will start working on the basic elements of the software. The goal for this week is to achieve a graphical view that would represent the game at some given state. Then the next week could be used to get the game actually running and updating the state.

## Project status 
The project enviroment with the libraries works fine, time to start actual development.

### TODOs

Implement classes Enemy and Tile (Miikka)

Implement classes Tower and Gamestate (Petteri)

Implement the basic GUI view with the tiles (Joel)

Implement GUI elements representing enemies and towers (Petrus)

Combine previously mentioned into a view of a gamestate (Everyone)

# Meeting 2 (21.11.2022 14:00)

## Attendees
Joel Toppinen

Miikka Åsnabrygg

Petrus Nikoskinen

Petteri Kippo

## Summary of works

Joel created the GUI class to represent the base for the graphical view and refractored tests into a simple format.
Miikka created Tile and Enemy classes to represent different tiles and enemies within the game engine.
Petteri started working on the Tower classes and the logic on how they interact with the enemies.
Petrus debugged some SFML view issues and started working on the graphical sprites that represent the enemies and towers.


## Challenges

Splitter enemy splitting needs to be figured out at some point (Requires inserting new enemies into the tiles). Petrus had some issues in getting the SFML view to show, which was solved with some magical button combination.

## Actions

We will start working on getting the main loop for the software functional so that the game can actually progress. The goal for the week is to get a single map / wave running by itself. Then the week after will be left to create the tools for the user to interact with the game, choosing levels and setting towers etc.

## Project status 
Most of the base classes have been implemented with most of the functionalities. The GUI class can represent view of the map made of tiles.

### TODOs

Methods for moving enemies, shooting towers (Petteri)

The main program that runs the loop that updates the game status (Joel)

Finishin up the graphical sprites (Petrus)

The file / map storage and initialization tools (Miikka)


# Meeting 3 (29.11.2022 13:00)

## Attendees
Joel Toppinen

Miikka Åsnabrygg

Petrus Nikoskinen

Petteri Kippo

## Summary of works

Joel implemented a bunch of the UI / gameplay features like pause/play button and capability to place towers on the map by dragging them from a menu at the edge of the screen.

Miikka created the tools to read and build maps from a file, as well as a method for moving all of the enemies.

Petteri implemented the rest of the methods for the first tower and started working on the rest of them.

Petrus worked on the tower/enemy sprites, they are nrealy finished.

## Challenges

The suitability of SFML by itself for UI development is found absolutely horrendous. However the schedule is tight so we will have to make do with what we got. The resulting UI might not look pretty but it works and suits the scale of the project. - Joel

## Actions

The aim for this week is to get a single map running as a game. This could then be used in the Demo. All that would be left for the final week would then be the option to choose different maps as well as some other additional bonus features.

## Project status 

Most of the functional parts currently work and the UI has most of the final features fully operational. Currently a single enemy moves through the map and a tower can be placed to stop it.

### TODOs

Waves and enemy spawning (Miikka)

All towers done, reward/target position system (Petteri)

Implement above features into the main game loop (Joel)

Finishing UI (Joel)

Sprites for towers and enemies implemented (Petrus)

Initial menu?

Firing animation? (Joel, if time)


# Meeting 3 (29.11.2022 13:00)

## Attendees
Joel Toppinen

Miikka Åsnabrygg

Petrus Nikoskinen

Petteri Kippo

## Summary of works

Miikka implemented the wave system and the map now plays through all of its waves. Petteri finished all of the towers and they now tell where they shoot and whether any money was earned as a result of an enemy dying. Joel implemented all of the towers into the UI placement options and created a firing animation for the towers. Petrus implemented a basic version of a tower/enemy sprite and made it render into the window.

## Challenges

BUG: Splitter death in tile 0 causes seg fault (Miikka)

BUG: Pawn placement on last row causes seg fault (Petteri)

## Actions

We need to implement a way to cycle through the maps as well as create the rest of them. Rest of the sprite textures need to be created as well. An idea is to add the visualization for the tower range when placing it, as well as potentially add sound effect for the game as well.

## Project status 

The game currently plays the one map successfully. The last week also requires us to spend time in creating both the documentation as well as the presentation for the project so extra features added at this point will be limited.

### TODOs

All textures finished + possibly sounds? (Petrus)

Methods for fetching tower ranges for placement info (Petteri)

Extra maps (Petteri)

Tower range visualisation (Joel) 

Map cycling (Miikka)

End game screen? (Joel)



