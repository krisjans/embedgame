#include <stdio.h>
#include "platform_helpers.h"
#include <vector>

using namespace std;

enum COLORS {
    BLACK = 30,
    YELLOW = 32,
    RED = 31,
};

class Point {
public:
    int x;
    int y;
    Point(int xx, int yy): x(xx), y(yy) {}

    bool operator==(const Point &p){
	return (x == p.x && y == p.y);
    }
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
	if (isHead(Point(x,y))){ return YELLOW; };
	if (isTail(Point(x,y))){ return RED; };

	return BLACK;
    }


    bool isHead(Point p){
	return (head == p);
    }

    bool isTail(Point p){
	return (tail == p);
    }


};

int main(int argc, char **argv) {
    const int WIDTH = 80;
    const int HEIGHT = 30;
    SnakeGame game(WIDTH, HEIGHT);

    clearScreen();

    while(1){
	if (getkey() != -1) {
	    break;
	}

	for(int x=0; x<WIDTH; x++){
	    for(int y=0; y<HEIGHT; y++){
		setCursorLocation(x, y);
		setTextColor(game.pixelColor(x,y), 1);
		printf("%c",  '*');
	    }
	}
    }

//    printf("hello2\n\n");
//    int x = 0, y=2;
//    char c = '0';
//    while (1) {
//	if (getkey() != -1) {
//	    break;
//	}
//	++x;
//	if (x > 80) {
//	    x = 1;
//	    ++y;
//	    if (y > 30) {
//		y = 1;
//		++c;
//		if (c > 'z') {
//		    c = '*';
//		}
//		if (c >= '0' && c <= '7') {
//		    setTextColor(c - '1' + 30, 1);
//		}
//	    }
//	}
//	setCursorLocation(x, y);
//	printf("%c", c);
//	sleep_ms(1);
//    }
//    setCursorLocation(1, 31);
//    printf("~~~~~~~~~~End~~~~~~~~~~~\n");
    return 0;
}
