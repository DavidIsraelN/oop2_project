# oop2_project - Bubble Trouble Game
final project in oop2 course


// ------------------------------------------------------
# Written by: 
    Mordechai Atiya. id - 208484576.
    David Israel Naki. id - 204647168.

// ------------------------------------------------------
# About this program:

    "Bubble Trouble" is a fast-paced shooting game.
    Shoot and split bouncing bubbles without getting hit to score points.
    Avoid collisions - three strikes and you're out.
    Power-ups offer extra lives and time.
    Three levels, increasing difficulty.
    Aim, shoot, dodge, and have a blast!

// ------------------------------------------------------
# Files we created:

- ResourcesManager  - Singleton - Source class for all program data.
                      Loading the files of the program once - textures, audio, texts, font.
                      and receiving the data from anywhere in the program.

- TimerManager      - Singleton - Timer class for all program timers.
                      Create the Timer of the program once and get to him from anywhere in the program.

- Sound             - Singleton - Sound class for all program sounds.
                      Create the Sounds of the program once and play from anywhere in the program.

- Colors            - Some custom colors for the game.

- Menu              - Responsible for menu screen and all its operation.

- EnumAndMacros     - Enum class for the game operation. The order of the firsts elements
                      (levels and game over) is very important for the operation of the game!

- Button            - An abstract class that is responsible for all the buttons.
                        - NewGame       - Inherit class for New Game button.
                        - ChooseLevel   - Inherit class for Level Choose button.
                        - Help          - Inherit class for Help button.
                        - Records       - Inherit class for Records button.
                        - Exit          - Inherit class for Exit Game button.
                        - MenuButton    - Inherit class for Menu button.
                        - Back          - Inherit class for Back button.
                        - Mute          - Inheritance class for the Mute button.

- Object            - An abstract class that is responsible for all the object of the game.
                      The subclasses of this class are:
                      * StaticObject    - An empty abstract class for all static objects of the game.
                          Its inheritance: Door, Wall.

                       * MovingObject   - An abstract class for all moving objects of the game.
                         its inheritance: Player, Ball, Weapon (include: GunWeapon),
                                          Gift (include: LifeGift, TimeGift, DefenseGift).

- Controller          - Main class that responsible for starting and ending the game.

- Board               - Responsible for all the gameplay, receiving the input from the player
                        and display the game to the screen.

- Level               - Responsible for the levels. Loads the desired level, contains in vectors all the level objects,
                        Responsible for performing the actions required in the current level
                        according to the existing situation.

- LevelReader         - Responsible for reading the correct file of the level, and extracting the data from it.


- StatusBar           - Responsible for the status bar of the game.
                        Presents level number, life, score and the time left to finish.

- GameOver            - Responsible for game over screen, and set the score to Record file if needed.

// ------------------------------------------------------
# Main data structure:

    The Controller store: Menu and Board.
    The Board store: Level, StatusBar, and GameOver.
    The Level store all the objects that are in the current level.

// ------------------------------------------------------
# Noteworthy algorithm:



// ------------------------------------------------------
# bugs that we know:


// ------------------------------------------------------
# Notes:

    We wanted to make two or three different types of weapons,
    as well as a gift that would give the player protection,
    but we didn't have time to do that.