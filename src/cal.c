#include <cal.h>
#include <cutils.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <clock.h>

static Date months[12] = {
    {31, 0},
    {28, 3},
    {31, 3},
    {30, 6},
    {31, 1},
    {30, 4},
    {31, 6},
    {31, 2},
    {30, 5},
    {31, 0},
    {30, 3},
    {31, 5}
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
    new_month("January",  0);
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

int *gen_days(int month, int days[4*128]) {
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

    int amt_weeks = (int)set_month.len+set_month.start_push/7;

    int i;
    int h = CAL_TOP_SPACING;
    int w = CAL_W_PADDING;
    
    char *nm_name = nmonths[month].name;
    strcat(nm_name, ", ");
    
    string_edit(CAL_LABEL_X, CAL_LABEL_Y, nm_name, strlen(nm_name));

    for (i = 0; i < amt_weeks; i++) {
        w += 3;

        if (w >= CAL_W_STOP) {
            h += CAL_H_SPACING;
            w = CAL_W_PADDING;
        }

        char day[128];
        snprintf(day, 128, "%d", days[i]);
        if (days[i] > -1) {
            string_edit(w, h, day, 2);
        }
    }
    return strlen(nm_name);
}