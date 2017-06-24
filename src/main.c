#include <keyboard.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cal.h>
#include <clock.h>

int refresh(int month) {
    puts("\e[2J"); //clear screen
    
    populate_nmonths();

    int days[4*128];
    gen_days(month, days);
    return draw_cal(days, month);
}

int main() {
    puts("\e[2J"); //clear screen
    hide_caret();

    char key;
    int month = 0;

    int spacing = refresh(0);
    char old[128];

    char buffer[128];

    while (1) {
        key = getch(0);
        if (key != 0) {
            if (key == 'q') {
                show_caret();
                break;
            }
            if (key == 'd') {
                month++;
                if (month == 12) {
                    month = 0;
                }
                spacing = refresh(month);
            }
            if (key == 'a') {
                month--;
                if (month < 0) {
                    month = 11;
                }
                spacing = refresh(month);
            }
        } 
        update(spacing, buffer);
        if (strcmp(old, buffer) == 1) {
            spacing = refresh(month);
        }
        strcpy(old, buffer);
    }
}