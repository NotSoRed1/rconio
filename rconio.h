#ifndef __RCONIO_H__

#define __RCONIO_H__

#define __WINDOWS__


#include<stdio.h>
#include<stdlib.h>


#ifdef __WINDOWS__

typedef enum
{
    BLACK           = 0,          
    BLUE            = 1,           
    GREEN           = 2,          
    CYAN            = 3,           
    RED             = 4,            
    MAGENTA         = 5,        
    BROWN           = 6,          
    LIGHTGRAY       = 7,      
    DARKGRAY        = 8,       
    LIGHTBLUE       = 9,      
    LIGHTGREEN      = 10,     
    LIGHTCYAN       = 11,      
    LIGHTRED        = 12,       
    LIGHTMAGENTA    = 13,   
    YELLOW          = 14,         
    WHITE           = 15
} COLORS;



#elif __LINUX__     // __WINDOWS__

typedef enum {
    BLACK       = 0,
    RED         = 1,
    GREEN       = 2,
    YELLOW      = 3,
    BLUE        = 4,
    MAGENTA     = 5,
    CYAN        = 6,
    WHITE       = 7

} COLORS;



#endif              // __LINUX__



void gotoxy(int x, int y);

void printxy(int x, int y, const char *format, ...);

void c_printxy(COLORS color, int x, int y, const char *format, ...);

void clrscr(void);

void getch(void);

void textcolor(COLORS color);

void bgcolor(COLORS color);

void get_terminal_infos(int *width, int *height);


#endif              // __RCONIO_H__