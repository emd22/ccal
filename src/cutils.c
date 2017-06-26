#include <cutils.h>
#include <keyboard.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int term_height() {
  struct winsize size;
  ioctl(1/*STDOUT_FILENO*/, TIOCGWINSZ, &size);
  return size.ws_row;
}

int term_width() {
  struct winsize size;
  ioctl(1/*STDOUT_FILENO*/, TIOCGWINSZ, &size);
  return size.ws_col;
}

void error(char *message) {
    puts("Error:");
    puts(message);
    putchar('\n');
    exit(1);
}

void edit(int x, int y, char ch, int color) {
    caret_position(x, y);
    colored_text(ch, color);
}

void string_edit(int x, int y, char *str, int len, int color) {
    int i;
    for (i = 0; i < len; i++) {
        edit(x+i, y, str[i], color);
    }
}

char *int_to_str(int n) {
    char *str;
    snprintf(str, 128, "%d", n);
    return str;
}

void colored_text(char ch, int color) {
    printf("\033[%dm%c\033[15m", color, ch); //pretty nasty ansi code
    printf("\033[%dm\033[15m", DEFAULT_COLOR);  
}

void time_delay(int ms) {
    usleep(ms * 1000);
}