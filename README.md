# ENGG1340_Sem2_Project_Group105

- Group No.: 105
- Group members: Ip Cheuk Wun Justus ( 3035789485 ) , Tam Chun Hoi Adrian ( 3035784758 )
- Topic: Pokemon ~Untold Tales of the Void~



## Game Description
Inspired by the game, Pokemon ~Untold Tales of the Void~ is an open-world text-based RPG about the adventure in a fantasy world full of Pokemons. A giant void has been in the center of the island for several millions of years. No one knows clearly what is inside the void. Legends have said that only the most worthy Pokemon trainers can survive and defeat the King of Underworld inside the void. Every now and then, brave adventurers group together and desire to reveal the secrets of the void. However, never was there one that could return after entering it. 

Britney is a new Pokemon trainer who just graduated from the Pokemon Academy. She lives in a village near to the void and she was fasinated to find out whats inside that deep giant hole. However, she was not convinced by the tales and rumours of the void. Therefore, she decided to go into the void on her own to find out. Out of curiousity, she sneaked into the void on a dark, foggy night. Without causing the attention of the entrance guards…

What will happen to Britney? Will she survive in the void? Will she defeat the King of Underworld? Let the journey begin!



## Game rules

### Background information
- The player will play as Britney to explore the Void.
- Players will be able to interact with different characters inside the Void map.
- Players can choose to kill or escape from the pokemons throughout the game.
- Players will be able to upgrade their own Pokemons through fighting other Pokemons.
- Players can save their current game progress in the checkpoint of each level.
- Players have to explore all 3 levels of the void. As players go deepe, it will become more difficult and infested with dangerous monsters. Players will have to fight the final boss to complete the game and acquire the ending.

### Basic Controls
- Navigating within the map using W, A, S, D keys.
- Interacting with different game events (e.g. game characters and savepoint) using "Space" bar.
- Choosing different dialogues or attacks using arrow keys.
- Confirming your choices using "Enter" key.



## Features

### Dynamic Dialogue System
- The dialogue system features a polymorphism design.
- The game’s dialogue system is based on a massive node network. It is stored in an external file which is loaded once the game starts.
- This feature fulfills the requirement of Generation of random game sets or events, File input/output, and Program code in multiple files.

### Gameplay system
- Turn-based battle system for the Pokemon fight.
- Players can navigate through the map and interact with items on the map using different keys
- Actual damage dealt with by the enemies is dynamic and will be affected by a random percentage (about 1-5%).
- These features fulfill the requirement of Generation of random game sets or events.

### Inventory System
- Pokeballs that are used to capture Pokemons can be stored inside the inventory system.
- Attributes such as health, damage and experience points (XP) will be stored individually for each Pokemon.
- This feature fulfills the requirement of Data structures for storing game status.

### Game Saving/Loading System
- The game’s current state including the player’s progress and Pokemon status such as health and XP will be saved into an external file.
- Different saving slots are available such that the players can restart the adventure without losing previous data.
- malloc(), free() and delete() keywords will be used when handling data structures like plot dialogue and damage output.
- This feature fulfills the requirement of Data structures for storing game status, Use of dynamic memory management and File input/output.



## External Libraries Used
- array
- chrono
- cmake
- cmath
- codecvt
- csignal
- cstdint
- cstring
- fstream
- iostream
- locale
- NlohmannJson
- optional
- random
- sstream
- string
- termios.h
- utility
- vector



## Compilation and Execution Instructions
```
git clone https://github.com/adriantam123/ENGG1340_Sem2_Project_Group105.git
cd ENGG1340_Sem2_Project_Group105
```
```
./Libraries/CMake/bin/cmake . && make && ./pokemon
```



## Remarks
- sample input / output files are not applicable as the game involves many random events (such as monsters appearing on the path randomly and various attack options). The user have to manually navigate the character using different keys, so no specific sample input / output can be provided.
