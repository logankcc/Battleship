/**
 * CISC 320 Fall 2021: Atomica group project
 *
 * Group members: Reid Moffat, Jacob Wong, Kaitlyn Hung
 */

#include "../include/screen/screenManager.h"

int main() {
    srand(time(NULL));
    screen::ScreenManager().run();

    return 0;
}
