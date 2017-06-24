#include <cutils.h>
#include <keyboard.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

String *str_alloc(int len, char *info) {
    String *string = malloc(sizeof(String));
    string->len = len;
    string->info = malloc(len+1);
    strcpy(string->info, info);
    return string;
}

void str_print(String *string) {
    puts(string->info);
}

void str_edit(String *string, int index, char to_add) {
    string->info[index] = to_add;
}

void str_cat_c(String *string, char *info, int info_len) {
    int current_len = strlen(string->info);
    int i;
    for (i = 0; i < info_len; i++) {
        str_edit(string, current_len+i, info[i]);
        printf("%d\n", string->len);
        string->len++;
    } 
}

void str_cat(String *string, String *string2) {
    str_cat_c(string, string2->info, string2->len);
}

void str_free(String *string) {
    free(string->info);
    free(string);
}

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

void edit(int x, int y, char ch) {
    caret_position(x, y);
    putchar(ch);
}

void string_edit(int x, int y, char *str, int len) {
    int i;
    for (i = 0; i < len; i++) {
        edit(x+i, y, str[i]);
    }
}

char *int_to_str(int n) {
    char *str;
    snprintf(str, 128, "%d", n);
    return str;
}