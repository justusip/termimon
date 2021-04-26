#include "Dialogue.h"

bool Dialogue::animationCompleted() {
    return cursor >= msg->size();
}
