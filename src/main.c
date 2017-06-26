#include <keyboard.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cal.h>
#include <clock.h>
#include <cutils.h>

int refresh(int month) {
    puts("\e[2J"); //clear screen
    
    populate_nmonths();

    int days[4*128];
    gen_days(month, days);
    return draw_cal(days, month);
}

void update_time(char *old, char *buffer, int month, int spacing) {
    update(spacing, buffer);
    if (strcmp(old, buffer) == 1) {
        spacing = refresh(month);
    }
    strcpy(old, buffer);
}

int main() {
    puts("\e[2J"); //clear screen
    hide_caret();

    char key;
    int month = get_mon();

    int spacing = refresh(month);
    char old[128];

    char buffer[128];

    //updates the time info once so it's not blank    
    update(spacing, buffer);
    update_time(old, buffer, month, spacing); 
    
    while (1) {
        key = kbhit();
        if (key != 0) {
            if (key == 'q') {
                show_caret();
                break;
            }
            if (key == 'd') {
                month++;
                if (month == 12) month = 0;
                spacing = refresh(month);
            }
            if (key == 'a') {
                month--;
                if (month < 0) month = 11;
                spacing = refresh(month);
            }
        } 
        update_time(old, buffer, month, spacing);
        time_delay(100);
    }
}