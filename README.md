# ENGG1340_Sem2_Project_Group105

- Group No.: 105
- Group members: Ip Cheuk Wun Justus ( 3035789485 ) , Tam Chun Hoi Adrian ( 3035784758 )
- Topic: Deep in Abyss 



## Game Description
Inspired by a TV series, Deep in Abyss is an open-world text-based RPG about the adventure into the void. The giant void has been in the center of the island for several millions of years. No one knows clearly what is inside the void. Legends have said that only the most worthy warriors can survive and defeat the King of the Underworld. Every now and then, brave adventurers group together and desire to reveal the secrets of the void. However, never was there one that could return after entering it. 

Britney lives in a village near to the void and she was fasinated to find out whats inside that deep giant hole. However, she was not convinced by the tales and rumours of the void. Therefore, she decided to go into the void on her own to find out. Out of curiousity, she sneaked into the void on a dark, foggy night. Without causing the attention of the entrance guards…

What will happen to Britney? Will she find her mother? Will she survive in the void? Let the journey begin!



## Game rules
- The player will play as Britney to explore the Endless Void.
- Inside the void, players will be able to interact with different characters.
- Players can choose to kill , escape or capture the monsters.
- Players can navigate within the map.
- Players have to explore all 3 levels of the void.
- Players can save their current game progress in the checkpoint of each level.
- As players go deeper into the void, it will become more difficult and infested with dangerous monsters.
- Level 1-2: both humans and monsters will appear in these levels, players can buy or upgrade their weapons and skills inside the shop run by the human characters, players     may encounter a few lucky human survivors which they can interact with.
- Level 3: Only monsters will appear in this level.
- At the end of level 3, players will have to fight the final boss to complete the game and acquire the ending.



## Features

### Dynamic Dialogue System
- The dialogue system features a polymorphism design.
- The game’s dialogue system is based on a massive node network. It is stored in an external file which is loaded once the game starts.
- This feature fulfills the requirement of Generation of random game sets or events, File input/output, and Program code in multiple files.

### Gameplay system
- Actual damage dealt with by the enemies is dynamic and will be affected by a random percentage (e.g. +5% / -5%).
- Buffs, debuffs, and critical rates will be implemented into the game. The effects of various buffs and debuffs are randomized. And the chances for critical hits will         increase with the critical rate of the character.
- These features fulfill the requirement of Generation of random game sets or events.

### Inventory System
- Weapons and items acquired by looting from monsters or purchasing from the store can be stored inside the inventory system.
- Attributes such as durability and damage can also be stored per item.
- This feature fulfills the requirement of Data structures for storing game status.

### Game Saving/Loading System
- The game’s current state including the player’s progress and status such as health and experience can be saved into an external file. It can then be retrieved next time the   game starts.
- Different saving slots are available such that the players can restart the adventure without losing previous data.
- malloc(), free() and delete() keywords will be used when handling data structures like plot dialogue and damage output.
- This feature fulfills the requirement of Data structures for storing game status, Use of dynamic memory management and File input/output.
