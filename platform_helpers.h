#ifndef PLATFORM_HELPERS_H_
#define PLATFORM_HELPERS_H_

void clearScreen();
void hideCursor();
void showCursor();
void setCursorLocation(int x, int y);
void setTextColor(int color, int bold = 1);
void sleep_ms(int milliseconds);
void initGetKey();
int getkey();
void deInitKey();

#endif /* PLATFORM_HELPERS_H_ */
