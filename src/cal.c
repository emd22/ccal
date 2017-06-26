#include <cal.h>
#include <cutils.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <clock.h>

static Date months[12] = {
    {31, 0}, //jan
    {28, 3}, //feb
    {31, 3}, //mar
    {30, 6}, //apr
    {31, 1}, //may
    {30, 4}, //jun
    {31, 6}, //jul
    {31, 2}, //aug
    {30, 5}, //sep
    {31, 0}, //oct
    {30, 3}, //nov
    {31, 5}  //dec

    //the first number is the number of days in the month.
    //the second is the push back for the calendar.
};

typedef struct {
    char name[16];
    int id;
} Month;

Month nmonths[128];

void new_month(char *name, int id) {
    Month month;
    strcpy(month.name, name);
    
    month.id = id;
    
    memcpy(&nmonths[id], &month, sizeof(month));
}

void populate_nmonths() {
    new_month("January",  0); //set the month name and index located
    new_month("Febuary",  1);
    new_month("March",    2);
    new_month("April",    3);
    new_month("May",      4);
    new_month("June",     5);
    new_month("July",     6);
    new_month("August",   7);
    new_month("September",8);
    new_month("October",  9);
    new_month("November", 10);
    new_month("December", 11);
}

Month get_month(char name[16]) {
    int i;
    for (i = 0; i < AMT_MONTHS; i++) {
        if (strcmp(nmonths[i].name, name) == 0) {
            return nmonths[i];
        }
    }
    error("Could not find month.");
}

Date get_date(int month) {
    return months[month];
}

int gen_days(int month, int days[4*128]) {
    Date set_month = get_date(month);
    int days_idx = 0; 
    int full_len = set_month.len+set_month.start_push;
    int day_len = set_month.len;

    int i;

    for (i = 0; i < set_month.start_push; i++) {
        days[i] = -1;
    }
    for (i = 0; i < full_len; i++) {
        days[i+set_month.start_push] = i+1; 
    }
}

void update(int space, char buffer[128]) {
    draw_time(CAL_LABEL_X+space, CAL_LABEL_Y, buffer);
}

int draw_cal(int *days, int month) {
    Date set_month = get_date(month);

    int h = CAL_TOP_SPACING;
    int w = CAL_W_PADDING;
    
    char *nm_name = nmonths[month].name;
    strcat(nm_name, ", ");
    
    string_edit(CAL_LABEL_X, CAL_LABEL_Y, nm_name, strlen(nm_name), DEFAULT_COLOR);

    int color;
    int cur_day = get_day();
    int cur_mon = get_mon();

    int i;
    for (i = 0; i < set_month.len+set_month.start_push; i++) {
        w += 3;

        if (w >= CAL_W_STOP) {
            h += CAL_H_SPACING;
            w = CAL_W_PADDING;
        }

        char day[3];
        snprintf(day, 3, "%d", days[i]);
        if (days[i] > -1) {
            color = DEFAULT_COLOR;
            if (days[i] == cur_day && month-1 == cur_mon-1) {
                color = 46/*background cyan*/;
            }
            string_edit(w, h, day, 2, color);
        }
    }
    return strlen(nm_name);
}