#include <stdio.h>
#include "platform_helpers.h"
#include <vector>
#include <math.h>

using namespace std;

enum COLORS {
    BLACK = 30,
    YELLOW = 32,
    RED = 31,
    BLUE = 34,
};

enum DIRECTIONS {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

enum GAME_STATE {
    RUNNING,
    GAME_OVER
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
    vector<Point> eggs;

    vector<Point> body;
public:
    SnakeGame(int w, int h): width(w), height(h), head(w / 2, h / 2), direction(LEFT), length(5){
	body.push_back(head);
	eggs.push_back(generateNextEgg());
    }
    COLORS pixelColor(int x, int y) {
	if (isHead(Point(x,y))){ return YELLOW; };
	if (isBody(Point(x,y))){ return RED; };
	if (isEgg(Point(x,y))){ return BLUE;}

	return BLACK;
    }
    GAME_STATE tick() {
	switch(direction) {
	case UP:
	    head.y--;
	    if (head.y < 0) {
		head.y = height - 1;
	    }
	    break;
	case DOWN:
	    head.y++;
	    if (head.y >= height) {
		head.y = 0;
	    }
	    break;
	case LEFT:
	    head.x--;
	    if (head.x < 0) {
		head.x = width - 1;
	    }
	    break;
	case RIGHT:
	    head.x++;
	    if (head.x >= width) {
		head.x = 0;
	    }
	    break;
	}
	if (isEgg(head)) {
	    length += 5;
	    eggs.pop_back();
	    eggs.push_back(generateNextEgg());
	}
	bool isMaxSizeReached = body.size() > length - 1;
	if (isMaxSizeReached) {
	    body.pop_back();
	}
	if(isBody(head)) {
	    return GAME_OVER;
	}

	body.insert(body.begin(), head);
	return RUNNING;
    }


    void changeDirection(DIRECTIONS d){
	if( d == UP && direction == DOWN) return;
	if( d == DOWN && direction == UP) return;
	if( d == LEFT && direction == RIGHT) return;
	if( d == RIGHT && direction == LEFT) return;

	direction = d;
    }

    bool isHead(Point p) {
	return (head == p);
    }

    bool isEgg(Point p) {
	return isVectorContainsPoint(p, eggs);
    }

    bool isBody(Point p) {
	return isVectorContainsPoint(p, body);
    }

    bool isVectorContainsPoint(Point p, vector<Point> &points) {
	for (auto& b : points) {
	    if (b == p) {
		return true;
	    }
	}
	return false;
    }


private:
    Point generateNextEgg() {
	return Point(rand() % width, rand() % height);
    }
};



int main(int argc, char **argv) {
    const int WIDTH = 80;
    const int HEIGHT = 30;
    SnakeGame game(WIDTH, HEIGHT);

    initGetKey();
    clearScreen();
    hideCursor();

    while(1){
	sleep_ms(150);
	switch(getkey()){
	case 'w': game.changeDirection(UP); break;
	case 'a': game.changeDirection(LEFT); break;
	case 's': game.changeDirection(DOWN); break;
	case 'd': game.changeDirection(RIGHT); break;
	case 'q':
	    deInitKey();
	    showCursor();
	    return 0;
	}

	GAME_STATE state = game.tick();
	if (state == GAME_OVER) {
	    break;
	}

	for(int x=0; x<WIDTH; x++){
	    for(int y=0; y<HEIGHT; y++){
		setCursorLocation(x+5, y+5);
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
    deInitKey();
    showCursor();
    return 0;
}
