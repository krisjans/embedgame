#include <stdio.h>
#include "platform_helpers.h"
#include <vector>

using namespace std;

enum COLORS {
    BLACK = 31,
    RED = 33,
};

class Point {
public:
    int x;
    int y;
    Point(int xx, int yy): x(xx), y(yy) {}
};

class SnakeGame {
    int width;
    int height;
    Point head;
    Point tail;

public:
    SnakeGame(int w, int h): width(w), height(h), head(w / 2, h / 2), tail(head) {
    }
    COLORS pixelColor(int x, int y) {
	return BLACK;
    }

};

int main(int argc, char **argv) {
    clearScreen();
    printf("hello2\n\n");
    int x = 0, y=2;
    char c = '0';
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
		if (c >= '0' && c <= '7') {
		    setTextColor(c - '1' + 30, 1);
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
