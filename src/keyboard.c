#include <keyboard.h>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void caret_position(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void hide_caret() {
    fputs("\e[?25l", stdout);
}

void show_caret() {
    fputs("\e[?25h", stdout);
}

char getch(int echo) {
    char c;   
    static struct termios oldt, newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr(STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON); 

    /*If echo is 0, it will hide the key pressed from being
      printed*/

    if (!echo) newt.c_lflag &= ~ECHO;

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    c = getchar();                

    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

int _kbhit() { //the purpose of kbhit is so it doesn't pause the
               //process while getting keyboard input like getch.
               //this can be espesially useful for doing a constant
               //process such as updating the time.
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char kbhit() {
    int key_pressed = _kbhit();
    if (key_pressed) {
        char key = getchar();
        return key;
    }
    return 0;
}