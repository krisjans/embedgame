#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

void sleep_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

static struct termios orig_term_attr;

void initGetKey() {
    struct termios new_term_attr;

    // set the terminal to raw mode
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    fcntl (STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

char getkey() {

    char character;
   // read a character from the stdin stream without blocking
    //   returns EOF (-1) if no character is available
    if (read(STDIN_FILENO, &character, 1) != 1) {
	character = 0;
    }

    return character;
}

void deInitKey() {
    // restore the original terminal attributes
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);
}

void clearScreen() {
    printf("\033[H\033[J");
}

void hideCursor() {
    printf("\033[?25l");
}

void showCursor() {
    printf("\033[?25h");
}

void setCursorLocation(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void setTextColor(int color, int bold) {
    printf("\033[%d;%dm", bold, color);
}
