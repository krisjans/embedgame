#ifndef PLATFORM_HELPERS_H_
#define PLATFORM_HELPERS_H_

void clearScreen();
void setCursorLocation(int x, int y);
void setTextColor(int color, int bold);
void sleep_ms(int milliseconds);
int getkey();

#endif /* PLATFORM_HELPERS_H_ */
