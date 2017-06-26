#ifndef CAL_H
#define CAL_H

#include <keyboard.h>
#include <stdio.h>

#define CAL_W_PADDING 4
#define CAL_W_STOP 25
#define CAL_H_SPACING 2
#define CAL_TOP_SPACING 4

#define CAL_LABEL_Y 2
#define CAL_LABEL_X 4

#define AMT_MONTHS 12     

typedef struct {
    int len;
    int start_push;
} Date;

int gen_days(int month, int days[4*128]);
int draw_cal(int *days, int month);

void populate_nmonths();

void update(int space, char buffer[128]);

#endif