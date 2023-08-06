# oop2_project
final project in oop2 course


// ------------------------------------------------------
# Written by: 
Mordechai Atiya. id - 208484576.
David Israel Naki. id - 204647168.

// ------------------------------------------------------
# About this program:



// ------------------------------------------------------
# Files we created:

- ResourceManager.h - Singleton class:
                      Source class for all program data.
                      Loading the files of the program once - textures, audio, texts, fonts.
                      and receiving the data from anywhere in the program.

- Sound.h           - Singleton - Sound class for all program sounds.
                      Create the Sounds of the program once and play from anywhere in the program.

- Colors.h          - Some custom colors for the program.

- Menu.h/cpp        - show the main menu before the game starts, and in the game when you press ESC.
                      The subclasses of this class are:
                        - Button.h/cpp      - Abstract class for all button types.
                        - NewGame.h/cpp     - Inherit class for New Game button.
                        - ChooseLevel.h     - Inherit class for Level Choose button.
                        - help.h/cpp        - Inherit class for Help button.
                        - ExitGame.h        - Inherit class for Exit Game button.
                        - Back.h            - Inherit class for Back button.
                        - Mute.h            - Inheritance class for the Mute button.

- Object.h/cpp      - Abstract class for all game Objects.
                      The subclasses of this class are:
                      * StaticObj.h  - Abstract class for Non-moving game objects.
                        it includes two kinds:
                        - Erasable.h  - Abstract class for Erasable game objects.
                          His inheritance: Cookie.h, Door.h, Key.h,
                          Gift.h {include: FreezeGift.h, LifeGift.h, SuperPGift.h, TimeGift.h}.
                        - Wall.h - Inheritance class for the game object of Non-moving type.

                       * MovingObj.h  - Abstract class for game objects that can move on the board (Moving).
                         His inheritance: Pacman.h/cpp, Demon.h/cpp.

- Controller.h/cpp   - Main class that run the game and the menu when needed.

- LevelManager.h/cpp - This class is responsible for selecting and running the levels, running the status bar,
                       moving the Objects, checking for collisions, changing level when the previous one is over,
                       and running the game over.

- InfoBar.h/cpp      - Class for the game information bar.
                       Display the level number, life left, score, timer.

- Timer.h/cpp        - Class that is responsible for the time of the game.

- LevelReader.h      - Class that is responsible for reading the correct file of the level,
                       and extracting the data from it.

- Level.h/cpp        - This class is responsible for the current level, displaying the level,
                       checking for collisions and responding, deleting eaten objects, etc..

- GameOver.h         - Class for displaying the game over screen, receives the score from the user,
                       and displays GameOver.

- Movement.h/cpp      - Abstract class with 2 inheriting classes that are responsible for the legality of Movement in game.
                        * Regular Movement - does not go through walls and doors.
                        * Super Pacman Movement - goes through doors, besides walls.

// ------------------------------------------------------
# Main data structure:


// ------------------------------------------------------
# Noteworthy algorithm:



// ------------------------------------------------------
# bugs that we know:


// ------------------------------------------------------
# Notes -

