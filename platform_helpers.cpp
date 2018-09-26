#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>

void sleep_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    // set the terminal to raw mode
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    // read a character from the stdin stream without blocking
    //   returns EOF (-1) if no character is available
    character = fgetc(stdin);

    // restore the original terminal attributes
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

void clearScreen() {
	printf("\033[H\033[J");
}

void setCursorLocation(int x, int y) {
	printf("\033[%d;%dH", y, x);
}
