#ifndef CUTILS_H
#define CUTILS_H

#include <stdio.h>

#define ASSERT(c,m) if(!c){puts(m);exit(1);}
#define putn(n) char buf[8];snprintf(buf,8,"%d",n);puts(buf);
#define DEFAULT_COLOR 0

int term_height();
int term_width();

void error(char *message);

void edit(int x, int y, char ch, int color);
void string_edit(int x, int y, char *str, int len, int color);

char *int_to_str(int n);

void colored_text(char ch, int color);
void time_delay(int ms);

#endif