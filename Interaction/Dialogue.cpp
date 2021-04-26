#include "Dialogue.h"

//managing dialogues
bool Dialogue::animationCompleted() {
    return cursor >= msg->size();
}
