#pragma once
#include <string>
#include <windows.h>
#include <sstream>
int s_width = 80;
int s_height = 35;
using namespace std;

#define redF FOREGROUND_RED | FOREGROUND_INTENSITY
#define redB BACKGROUND_RED | BACKGROUND_INTENSITY
#define blueF FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define blueB BACKGROUNDGROUND_BLUE | BACKGROUND_INTENSITY
#define greenF FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define greenB BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define whiteF FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define whiteB BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY

class cgame
{
private:
    HANDLE outhnd;
    HANDLE inhnd;
    SMALL_RECT rect_win;

    COORD characterPos = {0, 0};
    COORD buffersize = {short(s_width), short(s_height)};

public:
    cgame()
    {

        outhnd = GetStdHandle(STD_OUTPUT_HANDLE);
        inhnd = GetStdHandle(STD_INPUT_HANDLE);

        rect_win = {0, 0, (short)(s_width - 1), short(s_height - 1)};
    }
    void makeConsole()
    {

        SetConsoleWindowInfo(outhnd, TRUE, &rect_win);
        SetConsoleScreenBufferSize(outhnd, buffersize);
    }
    void DrawPoint(int x, int y, short col, CHAR_INFO *buffscreen)
    {
        buffscreen[x + s_width * y].Char.UnicodeChar = 0x25CF;
        buffscreen[x + s_width * y].Attributes = col;
    }
    void display(CHAR_INFO *buffscreen)
    {
        WriteConsoleOutputW(outhnd, buffscreen, buffersize, characterPos, &rect_win);
    }
    void fill(CHAR_INFO *buffscreen)
    {
        for (int i = 0; i < s_width * s_height; i++)
        {
            buffscreen[i].Char.UnicodeChar = ' ';
            buffscreen[i].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
        }
    }
    void DrawCell(int x, int y, short col, CHAR_INFO *buffscreen)
    {
        buffscreen[x + s_width * y].Char.UnicodeChar = 0x258A;
        buffscreen[x + s_width * y].Attributes = col;
    }
    void plotLineLow(int x0, int y0, int x1, int y1, short col, CHAR_INFO *buffscreen)
    {
        int dx = x1 - x0;
        int dy = y1 - y0;
        int yi = 1;
        if (dy < 0)
        {
            yi = -1;
            dy = -dy;
        }
        int D = 2 * dy - dx;
        int y = y0;

        for (int x = x0; x <= x1; x++)
        {
            DrawCell(x, y, col, buffscreen);
            if (D > 0)
            {
                y += yi;
                D -= 2 * dx;
            }
            D += 2 * dy;
        }
    }

    void plotLineHigh(int x0, int y0, int x1, int y1, short col, CHAR_INFO *buffscreen)
    {
        int dx = x1 - x0;
        int dy = y1 - y0;
        int xi = 1;
        if (dx < 0)
        {
            xi = -1;
            dx = -dx;
        }
        int D = 2 * dx - dy;
        int x = x0;

        for (int y = y0; y <= y1; y++)
        {
            DrawCell(x, y, col, buffscreen);

            if (D > 0)
            {
                x += xi;
                D -= 2 * dy;
            }
            D += 2 * dx;
        }
    }
    //Bresenham's algorithm for drawing line
    void Line(int x0, int y0, int x1, int y1, short col, CHAR_INFO *buffscreen)
    {

        if (abs(y1 - y0) < abs(x1 - x0))
        {
            if (x0 > x1)
            {
                plotLineLow(x1, y1, x0, y0, col, buffscreen);
            }
            else
            {
                plotLineLow(x0, y0, x1, y1, col, buffscreen);
            }
        }
        else
        {
            if (y0 > y1)
            {
                plotLineHigh(x1, y1, x0, y0, col, buffscreen);
            }
            else
            {
                plotLineHigh(x0, y0, x1, y1, col, buffscreen);
            }
        }
    }

    void drawBLock(int x, int y, int b_width, int b_height, short col, CHAR_INFO *bufferscreen)
    {

        int hn = b_height / 2;
        int wn = b_width / 2;

        if (wn < 1)
            wn = 1;
        for (int i = -hn; i < hn; i++)
        {
            for (int j = -wn; j < wn; j++)
            {
                bufferscreen[x + j + s_width * (y + i)].Char.UnicodeChar = 0x2588;
                bufferscreen[x + j + s_width * (y + i)].Attributes = col;
            }
        }
    }
    void DrawStringFromInt(int x, int y, short col, int b, CHAR_INFO *buffscreen)
    {
        std::wostringstream ws;
        ws << b;

        std::wstring a=L"Number of swaps : "+(ws.str());

        for (size_t i = 0; i < a.size(); i++)
        {
            buffscreen[x + i + s_width * y].Char.UnicodeChar = a[i];
            buffscreen[x + i + s_width * y].Attributes = col;
        }
    }
    void DrawString(int x, int y, short col, wstring a, CHAR_INFO *buffscreen)
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            buffscreen[x + i + s_width * y].Char.UnicodeChar = a[i];
            buffscreen[x + i + s_width * y].Attributes = col;
        }
    }
};

