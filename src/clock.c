#include <clock.h>
#include <cutils.h>

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_day() {
    time_t rawtime;
    struct tm *info;

    time(&rawtime);

    info = localtime(&rawtime);

    char buf[32];
    strftime(buf, 32, "%d", info);

    return atoi(buf);
}

int get_mon() {
    time_t rawtime;
    struct tm *info;

    time(&rawtime);

    info = localtime(&rawtime);

    char buf[32];
    strftime(buf, 32, "%m", info);

    return atoi(buf);
}


void draw_time(int x, int y, char buffer[128]) {
    char new_buf[128];

    time_t rawtime;
    struct tm *info;

    time(&rawtime);

    info = localtime(&rawtime);

    char year[16];
    char ntime[16];
    strftime(year, 16, "%Y - ", info); //<Year> - <Hour 12h>:<Minute>
    strftime(ntime, 16, "%I:%M%p", info);

    string_edit(x, y, year, strlen(year), 0);
    string_edit(x+strlen(year), y, ntime, strlen(ntime), 31/*foreground red*/);    
    strcat(new_buf, year);
    strcat(new_buf, ntime);
    strcpy(buffer, new_buf);
}