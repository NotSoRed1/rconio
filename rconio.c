#include "rconio.h"
#include <stdarg.h>
#include <stdio.h>
#include <vadefs.h>
#include <windows.h>




#ifdef __WINDOWS__

static COLORS _bgcolor = BLACK;
static COLORS _fgcolor = WHITE;

#include <windows.h>



void get_terminal_infos(int *width, int *height)
{
    CONSOLE_SCREEN_BUFFER_INFO infos;
    int result = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&infos);

    if (result) {
        *width = infos.srWindow.Right - infos.srWindow.Left + 1;
        *height= infos.srWindow.Bottom  - infos.srWindow.Top + 1;

    } else {
        *width = 105;
        *height = 27;
    }

}


void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = y;
    coordinates.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), 
                            coordinates );
}



void textcolor(COLORS color)
{
    _fgcolor = color;   
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
                            color + (_bgcolor << 4));
}


void bgcolor(COLORS color)
{
    _bgcolor = color;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
                            (color >> 4) + _fgcolor );

}

void clrscr()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO infos;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &infos))
        return;

    // Scroll the rectangle of the entire buffer.
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = infos.dwSize.X;
    scrollRect.Bottom = infos.dwSize.Y;

    // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - infos.dwSize.Y);

    // Fill with empty spaces with the buffer's default text attribute.
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = infos.wAttributes;

    // Do the scroll
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

    // Move the cursor to the top left corner too.
    infos.dwCursorPosition.X = 0;
    infos.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hConsole, infos.dwCursorPosition);
}


void printxy(int x, int y,const char *format, ...)
{
    va_list args;
    va_start(args, format);

    gotoxy(x, y);

    vprintf(format, args);
    va_end(args);
    fflush(stdout);
}


void c_printxy(COLORS color, int x, int y, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    textcolor(color);
    gotoxy(x, y);

    vprintf(format, args);
    va_end(args);
    fflush(stdout);
}


void getch(void)
{
    fflush(stdin);
    textcolor(_bgcolor);
    fgetc(stdin);
    textcolor(_fgcolor);
}


#elif __LINUX__     // __WINDOWS__

#include <sys/ioctl.h>

void get_terminal_infos(int *width, int *height)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    *width = w.ws_row;
    *height = w.ws_col

}
void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", x, y);
    fflush(stdout);
}


void printxy(int x, int y,const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("\033[%d;%dH", x, y);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
}


void c_printxy(COLORS color, int x, int y, const char *format, ...)
{
    textcolor(color);

    va_list args;
    va_start(args, format);
    printf("\033[%d;%dH", x, y);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
}


void clrscr(void)
{
    system("clear");
    fflush(stdout);
}


void getch(void)
{
    fflush(stdin);
    printf("\x1B[8m");
    fgetc(stdin);
    printf("\x1B[0m");
}

void textcolor(COLORS color)
{
    if (color > 7 || color < 0) {
        fputs("color number must be between 0 and 7", stderr);
        return ;
    }
    printf("\x1B[%dm", 30 + color);
    fflush(stdout);
}


void bgcolor(COLORS color)
{
    if (color > 7 || color < 0) {
        fputs("color number must be between 0 and 7", stderr);
        return ;
    }
    printf("\x1B[%dm", 40 + color);
    fflush(stdout);
}


#endif              // __LINUX__




