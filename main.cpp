/*
 *  ,-.----.
 *  \    /  \                  ,-.                    ____
 *  |   :    \             ,--/ /|                  ,'  , `.
 *  |   |  .\ :   ,---.  ,--. :/ |               ,-+-,.' _ |   ,---.        ,---,
 *  .   :  |: |  '   ,'\ :  : ' /             ,-+-. ;   , ||  '   ,'\   ,-+-. /  |
 *  |   |   \ : /   /   ||  '  /      ,---.  ,--.'|'   |  || /   /   | ,--.'|'   |
 *  |   : .   /.   ; ,. :'  |  :     /     \|   |  ,', |  |,.   ; ,. :|   |  ,"' |
 *  ;   | |`-' '   | |: :|  |   \   /    /  |   | /  | |--' '   | |: :|   | /  | |
 *  |   | ;    '   | .; :'  : |. \ .    ' / |   : |  | ,    '   | .; :|   | |  | |
 *  :   ' |    |   :    ||  | ' \ \'   ;   /|   : |  |/     |   :    ||   | |  |/
 *  :   : :     \   \  / '  : |--' '   |  / |   | |`-'       \   \  / |   | |--'
 *  |   | :      `----'  ;  |,'    |   :    |   ;/            `----'  |   |/
 *  -----------------------------  R  E  M  A  K  E  -----------------------------
 *
 *  ENGG1340 Project Section 2DE
 *  Group 105
 *
 *  Ip Cheuk Wun Justus
 *  Tam Chun Hoi Adrian
 */


#include <termios.h>
#include <csignal>
#include <fstream>

#include "Interface/Inputs.h"
#include "Mechanics/Game.h"
#include "Interface/Terminal.h"
#include "Misc/SaveManager.h"


void onShutdown(int s) {
    Inputs::reset();
    Terminal::clearScreen();
    Terminal::moveTo(0, 0);
    Terminal::cursorShown(true);
    exit(s);
}


//main function
int main() {
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = onShutdown;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    Terminal::cursorShown(false);
    Inputs::init();

    Game e;
    e.start();

    onShutdown(0);
    return 0;
}