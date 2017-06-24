#ifndef CUTILS_H
#define CUTILS_H

#include <stdio.h>

#define ASSERT(c,m) if(!c){puts(m);exit(1);}
#define putn(n) char buf[8];snprintf(buf,8,"%d",n);puts(buf);

typedef struct {
    int len;
    char *info;
} String;

String *str_alloc(int len, char *info);
void str_print(String *string);
void str_edit(String *string, int index, char to_add);
void str_cat_c(String *string, char *info, int info_len);
void str_cat(String *string, String *string2);
void str_free(String *string);

int term_height();
int term_width();

void error(char *message);

void edit(int x, int y, char ch);
void string_edit(int x, int y, char *str, int len);

char *int_to_str(int n);

#endif