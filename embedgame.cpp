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
    BROWN = 33,
};

enum DIRECTIONS {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    DIRECTION_COUNT,
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
    vector<Point> predators;
    vector<Point> body;

    int pendingEggs = 1;
    int pendingPredators = 0;
public:
    SnakeGame(int w, int h): width(w), height(h), head(w / 2, h / 2), direction(LEFT), length(5){
	body.push_back(head);
    }
    COLORS pixelColor(int x, int y) {
	if (isHead(Point(x,y))){ return YELLOW; };
	if (isBody(Point(x,y))){ return BROWN; };
	if (isEgg(Point(x,y))){ return BLUE;}
	if (isPredator(Point(x,y))){ return RED;}

	return BLACK;
    }
    GAME_STATE tick() {
	move(head, direction);
	if (isEgg(head)) {
	    length += 5;
	    eggs.pop_back();
	    ++pendingEggs;
	    ++pendingPredators;
	}
	bool isMaxSizeReached = body.size() > length - 1;
	if (isMaxSizeReached) {
	    body.pop_back();
	}
	if(isBody(head) || isPredator(head)) {
	    return GAME_OVER;
	}

	body.insert(body.begin(), head);

	generateNextEgg();
	generateNextPredator();
	return movePredators();
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

    bool isPredator(Point p) {
	return isVectorContainsPoint(p, predators);
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
    void spawnSomething(vector<Point> & somethings, int & counter) {
	if (counter <= 0) {
	    return;
	}
	Point point = Point(rand() % width, rand() % height);
	if (isBody(point) || isEgg(point) || isPredator(point)) {
	    return;
	}
	somethings.push_back(point);
	--counter;
    }
    void generateNextEgg() {
	spawnSomething(eggs, pendingEggs);
    }
    void generateNextPredator() {
	spawnSomething(predators, pendingPredators);
    }

    GAME_STATE movePredators() {
	for (auto& p : predators) {
	    DIRECTIONS d = (DIRECTIONS)(rand() % DIRECTION_COUNT);
	    move(p, d);
	    if (isBody(p)) {
		return GAME_OVER;
	    }
	}

	return RUNNING;

    }

    void move(Point &point, DIRECTIONS d) {
	switch(d) {
		case UP:
		    point.y--;
		    if (point.y < 0) {
			point.y = height - 1;
		    }
		    break;
		case DOWN:
		    point.y++;
		    if (point.y >= height) {
			point.y = 0;
		    }
		    break;
		case LEFT:
		    point.x--;
		    if (point.x < 0) {
			point.x = width - 1;
		    }
		    break;
		case RIGHT:
		    point.x++;
		    if (point.x >= width) {
			point.x = 0;
		    }
		    break;
		}
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
		COLORS color = game.pixelColor(x,y);
		setTextColor(color, 1);
		printf("%c",  color == BLACK ? ' ' : '*');
	    }
	}
    }

    deInitKey();
    showCursor();
    return 0;
}
