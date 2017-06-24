#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>

void caret_position(int x, int y);
void hide_caret();
void show_caret();
char getch(int echo);
char kbhit();

#endif