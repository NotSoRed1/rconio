#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rconio.h"

#define __WINDOWS__

void print_centered(const char *text) {
    int width;
    int height;

    get_terminal_infos(&width, &height);
    int x = (height/ 2);
    int y = (width / 2) - (12 / 2);
    
    textcolor(GREEN);
    printxy(x, y, text); 
    getch();
}


int main(void) 
{
    clrscr();
    textcolor(RED); gotoxy(14, 40); printf("test test");
    clrscr();
    getch();
    print_centered("hello world!");
    return 0;
}