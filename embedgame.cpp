#include <stdio.h>
#include "platform_helpers.h"
#include <vector>

using namespace std;

enum COLORS {
    BLACK = 30,
    YELLOW = 32,
    RED = 31,
};

enum DIRECTIONS {
    UP,
    DOWN,
    LEFT,
    RIGHT,
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
    DIRECTIONS direction;
    int length;

    vector<Point> body;
public:
    SnakeGame(int w, int h): width(w), height(h), head(w / 2, h / 2), direction(LEFT), length(5){
	body.push_back(head);
    }
    COLORS pixelColor(int x, int y) {
	if (isHead(Point(x,y))){ return YELLOW; };
	if (isBody(Point(x,y))){ return RED; };

	return BLACK;
    }
    void tick() {
	switch(direction) {
	case UP:
	    head.y--;
	    if (head.y < 0) {
		head.y = height;
	    }
	    break;
	case DOWN:
	    head.y++;
	    if (head.y > height) {
		head.y = 0;
	    }
	    break;
	case LEFT:
	    head.x--;
	    if (head.x < 0) {
		head.x = width;
	    }
	    break;
	case RIGHT:
	    head.x++;
	    if (head.x > width) {
		head.x = 0;
	    }
	    break;
	}
	body.insert(body.begin(), head);
	if(body.size() > length) {
	    body.pop_back();
	}
    }


    bool isHead(Point p){
	return (head == p);
    }



    bool isBody(Point p) {
	for (auto& b : body) {
	    if (b == p) {
		return true;
	    }
	}
	return false;
    }


};

int main(int argc, char **argv) {
    const int WIDTH = 80;
    const int HEIGHT = 30;
    SnakeGame game(WIDTH, HEIGHT);

    clearScreen();

    while(1){
	sleep_ms(50);
	if (getkey() != -1) {
	    break;
	}
	game.tick();

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
