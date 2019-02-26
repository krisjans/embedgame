#include <stdio.h>
#include "platform_helpers.h"

int main(int argc, char **argv) {
    clearScreen();
    printf("hello2\n\n");
    int x = 0, y=2;
    char c = '*';
    while (1) {
	if (getkey() != -1) {
	    break;
	}
	++x;
	if (x > 80) {
	    x = 1;
	    ++y;
	    if (y > 30) {
		y = 1;
		++c;
		if (c > 'z') {
		    c = '*';
		}
	    }
	}
	setCursorLocation(x, y);
	printf("%c", c);
	sleep_ms(1);
    }
    setCursorLocation(1, 31);
    printf("~~~~~~~~~~End~~~~~~~~~~~\n");
    return 0;
}
