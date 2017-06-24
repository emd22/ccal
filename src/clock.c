#include <clock.h>
#include <cutils.h>

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void draw_time(int x, int y, char buffer[128]) {
    char new_buf[128];

    time_t rawtime;
    struct tm *info;

    time(&rawtime);

    info = localtime(&rawtime);

    strftime(new_buf, 80,"%Y - %I:%M%p", info); //<Year> - <Hour 12h>:<Minute>

    string_edit(x, y, new_buf, strlen(buffer));
    strcpy(buffer, new_buf);
}